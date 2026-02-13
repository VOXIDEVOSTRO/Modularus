#include <__KCONF.h>
#include <Errors.h>

#include <VirtualFileSystem.h>
#include <System.h>/*sysfs++*/

#ifdef BUILTINS
    #include <BuiltIns/Device/UART.h>
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
    #endif

    #ifdef TESTING
        char Message[] = "\nHello World!\n";
        FILE* File = VFS_Open("/uart", VFS_OpenFlag_WRITEONLY, Error);
        VFS_Write(File, Message, strlen(Message), Error);
        VFS_Close(File, Error);
    #endif

    for(;;)
    {
        __asm__("hlt");
    }
}