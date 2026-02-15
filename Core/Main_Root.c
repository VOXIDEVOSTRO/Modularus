#include <__KCONF.h>
#include <Errors.h>

#include <VirtualFileSystem.h>
#include <System.h>/*sysfs++*/

#ifdef BUILTINS
    #include <BuiltIns/Device/UART.h>
    #include <BuiltIns/Logger/Emitter.h>
    #include <BuiltIns/Logger/Formatter.h>
    #include <BuiltIns/Linker/LinkerELF.h>
    #include <BuiltIns/Loader/Loader.h>
#endif

SYSTEM_ERROR Err;
SYSTEM_ERROR* Error = &Err;
    
void KernelMain(void)
{
    /*STANDARD*/
    VFS_KickStart(Error);

    /*sysfs++ as root*/
    System_KickStart(Error);
    VFS_Mount("", "/", "sysfs++", 0, 0, Error);

    /*BuiltIns*/
    #ifdef BUILTINS
        UART_KickStart(Error);
        Emitter_KickStart(Error);
        Loader_GetModules(Error); /*So the /loader can register itself*/
    #endif

    #ifdef TESTING
        KrnPrintf("\nHello World!\n");
        FILE* LoaderFile = VFS_Open("/loader", VFS_OpenFlag_WRITEONLY, Error);
        LOADED_MODULE Test;
        if (VFS_IOControl(LoaderFile, LoaderCommand_GET, &Test, Error) == GeneralOK)
        {
            KrnPrintf("Module: %s @ %p size %lu\n", Test.Name, Test.Address, Test.Size);
        }
        else
        {
            KrnPrintf("IoCtl failed, Errno %d, traceback: %d", Error->ErrorCode, Error->TraceBack);
        }
    #endif

    for(;;)
    {
        __asm__("hlt");
    }
}