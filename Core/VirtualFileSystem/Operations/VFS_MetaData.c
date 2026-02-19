#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_FStats(FILE* FileHandle, VFS_STAT* StatBuffer, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_FStats(Code) \
        ErrorOut(Error, NULL, Code, FUNC_VFS_FStats)
    
    if (Probe4Error(FileHandle) || !FileHandle || Probe4Error(StatBuffer) || !StatBuffer)
    {
        ErrorOut_VFS_FStats(-EINVAL);
        return Error->ErrorCode;
    }

    if (Probe4Error(FileHandle->Node) || !FileHandle->Node || Probe4Error(FileHandle->Node->Operations) || !FileHandle->Node->Operations || Probe4Error(FileHandle->Node->Operations->Stat) || !FileHandle->Node->Operations->Stat)
    {
        ErrorOut_VFS_FStats(-ENOSYS);
        return Error->ErrorCode;
    }

    return FileHandle->Node->Operations->Stat(FileHandle->Node, StatBuffer, Error);
}

int
VFS_Stats(const char* Path, VFS_STAT* StatBuffer, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_Stats(Code) \
        ErrorOut(Error, NULL, Code, FUNC_VFS_Stats)
    
    if (Probe4Error(Path) || !Path || Probe4Error(StatBuffer) || !StatBuffer)
    {
        ErrorOut_VFS_Stats(-EINVAL);
        return Error->ErrorCode;
    }

    DIRECTORY_ENTRY* DirectoryEntry = VFS_Resolve(Path, Error);
    if (Probe4Error(DirectoryEntry) || !DirectoryEntry || Probe4Error(DirectoryEntry->Node) || !DirectoryEntry->Node)
    {
        ErrorOut_VFS_Stats(-ENOENT);
        return Error->ErrorCode;
    }

    if (Probe4Error(DirectoryEntry->Node->Operations) || !DirectoryEntry->Node->Operations || Probe4Error(DirectoryEntry->Node->Operations->Stat) || !DirectoryEntry->Node->Operations->Stat)
    {
        ErrorOut_VFS_Stats(-ENOSYS);
        return Error->ErrorCode;
    }

    return DirectoryEntry->Node->Operations->Stat(DirectoryEntry->Node, StatBuffer, Error);
}
