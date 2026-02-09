#include <__KCONF.h>
#include <Errors.h>

#include <VirtualFileSystem.h>

SYSTEM_ERROR Err;
SYSTEM_ERROR* Error = &Err;
    
void KernelBoot(void)
{
    VfsInit(Error);

    for(;;)
    {
        __asm__("hlt");
    }
}