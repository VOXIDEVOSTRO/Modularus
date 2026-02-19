#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_MountTableEnumerate(char* Buffer, long Length, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_MountTableEnumerate(Code) \
        ErrorOut(Error, NULL, Code, FUNC_VFS_MountTableEnumerate)
 
    if (Probe4Error(Buffer) || !Buffer || Length <= 0)
    {
        ErrorOut_VFS_MountTableEnumerate(-EINVAL);
        return Error->ErrorCode;
    }

    long Offset = 0;
    for (long Iteration = 0; Iteration < MountsCount; Iteration++)
    {
        const char* Path = Mounts[Iteration].Path;
        long Index = (long)strlen(Path);
        if (Offset + Index + 2 >= Length)
        {
            break;
        }

        memcpy(Buffer + Offset, Path, (size_t)Index);
        Offset += Index;
        Buffer[Offset++] = '\n';
    }

    if (Offset < Length)
    {
        Buffer[Offset] = 0;
    }
    
    return (int)Offset;
}

int
VFS_MountTableFind(const char* Path, char* Buffer, long Length, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_MountTableFind(Code) \
        ErrorOut(Error, NULL, Code, FUNC_VFS_MountTableFind)
    
    if (Probe4Error(Path) || !Path || Probe4Error(Buffer) || !Buffer || Length <= 0)
    {
        ErrorOut_VFS_MountTableFind(-EINVAL);
        return Error->ErrorCode;
    }

    for (long Iteration = 0; Iteration < MountsCount; Iteration++)
    {
        if (strcmp(Mounts[Iteration].Path, Path) == 0)
        {
            long Index = (long)strlen(Mounts[Iteration].Path);
            if (Index >= Length)
            {
                ErrorOut_VFS_MountTableFind(-ENAMETOOLONG);
                return Error->ErrorCode;
            }

            memcpy(Buffer, Mounts[Iteration].Path, (size_t)(Index + 1));
            
            return GeneralOK;
        }
    }

    ErrorOut_VFS_MountTableFind(-ENOENT);
    return Error->ErrorCode;
}
