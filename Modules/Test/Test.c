#include <__KCONF.h>
#include <VirtualFileSystem.h>
#include <Errors.h>

SYSTEM_ERROR Err;
SYSTEM_ERROR* Error = &Err;

size_t
strlen(const char* String)
{
    size_t Size = 0;
    while (String[Size] != '\0')
    {
        Size++;
    }
    return Size;
}

int _start(void)
{
    /*Write down to the /uart BuiltIn*/
    FILE* Uart = VFS_Open("/uart", VFS_OpenFlag_WRITEONLY, Error);
    char String[] = "Test module active\n";
    VFS_Write(Uart, &String, strlen(String), Error);
    return 0;
}

int _exit(void)
{
    return 0;
}