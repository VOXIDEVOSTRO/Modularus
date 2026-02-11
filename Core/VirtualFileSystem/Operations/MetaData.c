#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VfsFstats(FILE* FileHandle, VFS_STAT* StatBuffer, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VfsFstats(Code) \
        ErrorOut(Error, Code, FUNC_VfsFstats)
    
    if (Probe4Error(FileHandle) || !FileHandle || Probe4Error(StatBuffer) || !StatBuffer)
    {
        ErrorOut_VfsFstats(-EINVAL);
        return -EINVAL;
    }

    if (Probe4Error(FileHandle->Node) || !FileHandle->Node || Probe4Error(FileHandle->Node->Operations) || !FileHandle->Node->Operations || Probe4Error(FileHandle->Node->Operations->Stat) || !FileHandle->Node->Operations->Stat)
    {
        ErrorOut_VfsFstats(-ENOSYS);
        return -ENOSYS;
    }

    return FileHandle->Node->Operations->Stat(FileHandle->Node, StatBuffer, Error);
}

int
VfsStats(const char* Path, VFS_STAT* StatBuffer, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VfsStats(Code) \
        ErrorOut(Error, Code, FUNC_VfsStats)
    
    if (Probe4Error(Path) || !Path || Probe4Error(StatBuffer) || !StatBuffer)
    {
        ErrorOut_VfsStats(-EINVAL);
        return -EINVAL;
    }

    DIRECTORY_ENTRY* DirectoryEntry = VfsResolve(Path, Error);
    if (Probe4Error(DirectoryEntry) || !DirectoryEntry || Probe4Error(DirectoryEntry->Node) || !DirectoryEntry->Node)
    {
        ErrorOut_VfsStats(-ENOENT);
        return -ENOENT;
    }

    if (Probe4Error(DirectoryEntry->Node->Operations) || !DirectoryEntry->Node->Operations || Probe4Error(DirectoryEntry->Node->Operations->Stat) ||
        !DirectoryEntry->Node->Operations->Stat)
    {
        ErrorOut_VfsStats(-ENOSYS);
        return -ENOSYS;
    }

    return DirectoryEntry->Node->Operations->Stat(DirectoryEntry->Node, StatBuffer, Error);
}
