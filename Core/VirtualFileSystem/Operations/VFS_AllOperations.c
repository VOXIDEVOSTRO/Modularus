#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_ReadAll(const char* Path, void* Buffer, long BufferLength, long* OutLength, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_ReadAll(Code) \
        ErrorOut(Error, Code, FUNC_VFS_ReadAll)
    
    FILE* FileHandle = VFS_Open(Path, VFS_OpenFlag_READONLY, Error);
    if (Probe4Error(FileHandle) || !FileHandle)
    {
        ErrorOut_VFS_ReadAll(-ENOENT);
        return Error->ErrorCode;
    }
    
    long Total = 0;
    while (Total < BufferLength)
    {
        long ReadIndex = VFS_Read(FileHandle, (char*)Buffer + Total, BufferLength - Total, Error);
        if (ReadIndex < 0)
        {
            VFS_Close(FileHandle, Error);
            
            ErrorOut_VFS_ReadAll(-ENOSPC);
            return Error->ErrorCode;
        }

        if (ReadIndex == 0)
        {
            break;
        }

        Total += ReadIndex;
    }

    if (OutLength)
    {
        *OutLength = Total;
    }

    VFS_Close(FileHandle, Error);
    
    return GeneralOK;
}

int
VFS_WriteAll(const char* Path, const void* Buffer, long Length, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_WriteAll(Code) \
        ErrorOut(Error, Code, FUNC_VFS_WriteAll)

    FILE* FileHandle = VFS_Open(Path, VFS_OpenFlag_CREATE | VFS_OpenFlag_WRITEONLY | VFS_OpenFlag_TRUNCATE, Error);
    if (Probe4Error(FileHandle) || !FileHandle)
    {
        ErrorOut_VFS_WriteAll(-ENOENT);
        return Error->ErrorCode;
    }

    long Total = 0;
    while (Total < Length)
    {
        long WriteIndex = VFS_Write(FileHandle, (const char*)Buffer + Total, Length - Total, Error);
        if (WriteIndex <= 0)
        {
            VFS_Close(FileHandle, Error);
            
            ErrorOut_VFS_WriteAll(-ENOSPC);
            return Error->ErrorCode;
        }

        Total += WriteIndex;
    }

    VFS_Close(FileHandle, Error);
    
    return GeneralOK;
}

int
VFS_SyncAll(SYSTEM_ERROR* Error)
{
    for (long Iteration = 0; Iteration < MountsCount; Iteration++)
    {
        SUPER_BLOCK* SuperBlock = Mounts[Iteration].SuperBlock;
        if (SuperBlock && SuperBlock->Operations && SuperBlock->Operations->Sync)
        {
            SuperBlock->Operations->Sync(SuperBlock, Error);
        }
    }
    
    return GeneralOK;
}