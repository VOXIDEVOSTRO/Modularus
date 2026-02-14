#include <__KCONF.h>
#include <Errors.h>
#include <BuiltIns/Loader/Loader.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

LOADED_MODULE* LoadedModules = NULL;

LOADED_MODULE*
Loader_GetModules(SYSTEM_ERROR* Error)
{
    #define ErrorOut_Loader_GetModules(Code) \
        ErrorOut(Error, Code, General)

    /* Request MODULE from boot services, simplest of all loaders it can be */
    BOOT_REQUEST Request = RequestBootService(RequestMODULE, Error);
    if (Probe4Error(Request.Pointer) || !Request.Pointer)
    {
        ErrorOut_Loader_GetModules(-BadRequest);
        return Error2Pointer(Error->ErrorCode);
    }

    /*LIMINE*/

    #ifdef BOOTVENDOR_Limine
        struct limine_module_response* Response = (struct limine_module_response*)Request.Pointer;

        if (!Response->modules || Response->module_count == 0)
        {
            ErrorOut_Loader_GetModules(-BadRange);
            return Error2Pointer(Error->ErrorCode);
        }

        LOADED_MODULE* First = NULL;
        LOADED_MODULE* Last = NULL;

        for (uint64_t Index = 0; Index < Response->module_count; Index++)
        {
            struct limine_file* File = Response->modules[Index];

            LOADED_MODULE* Module = KMalloc(sizeof(LOADED_MODULE), Error);
            if (Probe4Error(Module) || !Module)
            {
                continue;
            }

            const char* Name = File->path;
            const char* Basename = Name;
            for (const char* Component = Name; *Component; Component++)
            {
                if (*Component == '/') Basename = Component + 1;
            }

            Module->Name = Basename;
            Module->Address = File->address;
            Module->Size = File->size;
            Module->Next = NULL;

            if (!First)
            {
                First = Module;
            }

            if (Last) 
            {
                Last->Next = Module;
            }

            Last = Module;
        }

        LoadedModules = First;
        return First;
    #endif
}

LOADED_MODULE*
Loader_FindModule(const char* Name, SYSTEM_ERROR* Error)
{
    #define ErrorOut_Loader_FindModule(Code) \
        ErrorOut(Error, Code, General)

    for (LOADED_MODULE* Modules = LoadedModules; Modules; Modules = Modules->Next)
    {
        if (strcmp(Modules->Name, Name) == 0)
        {
            return Modules;
        }
    }

    ErrorOut_Loader_FindModule(-NotFound);
    return Error2Pointer(Error->ErrorCode);
}

uint64_t
Loader_GetModuleCount(SYSTEM_ERROR* Error __UNUSED)
{
    uint64_t Count = 0;
    for (LOADED_MODULE* Modules = LoadedModules; Modules; Modules = Modules->Next)
    {
        Count++;
    }
    return Count; /*Not Found(SYSTEM_ERROR enum btw) if 0*/
}
