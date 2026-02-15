#include <BuiltIns/Linker/LinkerELF.h>
#include <KExports.h>
#include <Errors.h>

void* Module_Link(void* image_base, SYSTEM_ERROR* err)
{
    Elf64_Ehdr* eh = (Elf64_Ehdr*)image_base;
    Elf64_Shdr* sh = (Elf64_Shdr*)((uint8_t*)image_base + eh->e_shoff);

    Elf64_Sym* symtab = 0;
    const char* strtab = 0;

    // find symtab + strtab
    for (int i = 0; i < eh->e_shnum; i++) {
        if (sh[i].sh_type == SHT_SYMTAB)
            symtab = (Elf64_Sym*)((uint8_t*)image_base + sh[i].sh_offset);
        if (sh[i].sh_type == SHT_STRTAB && i != eh->e_shstrndx)
            strtab = (const char*)((uint8_t*)image_base + sh[i].sh_offset);
    }

    if (!symtab || !strtab)
        return 0;

    // resolve undefined symbols
    for (Elf64_Sym* s = symtab; s->st_name; s++) {
        if (s->st_shndx == SHN_UNDEF) {
            const char* name = strtab + s->st_name;
            void* addr = LookUpKExport(name, err);
            if (!addr)
                return 0;
            s->st_value = (uint64_t)addr;
        }
    }

    // apply relocations
    for (int i = 0; i < eh->e_shnum; i++) {
        if (sh[i].sh_type != SHT_RELA)
            continue;

        Elf64_Rela* rela = (Elf64_Rela*)((uint8_t*)image_base + sh[i].sh_offset);
        int count = sh[i].sh_size / sizeof(Elf64_Rela);

        for (int r = 0; r < count; r++) {
            uint64_t type = ELF64_R_TYPE(rela[r].r_info);
            uint64_t sym  = ELF64_R_SYM(rela[r].r_info);

            uint8_t* target = (uint8_t*)image_base + rela[r].r_offset;
            uint64_t S = symtab[sym].st_value;
            uint64_t A = rela[r].r_addend;
            uint64_t P = (uint64_t)target;

            switch (type) {
                case R_X86_64_64:
                    *(uint64_t*)target = S + A;
                    break;

                case R_X86_64_PC32:
                    *(uint32_t*)target = (uint32_t)(S + A - P);
                    break;

                case R_X86_64_RELATIVE:
                    *(uint64_t*)target = (uint64_t)image_base + A;
                    break;

                default:
                    return 0;
            }
        }
    }

    return image_base;
}
