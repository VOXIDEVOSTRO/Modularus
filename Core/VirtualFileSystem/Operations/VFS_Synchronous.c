#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_FSync(FILE* FileHandle, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_FSync(Code) \
        ErrorOut(Error, NULL, Code, FUNC_VFS_FSync)
    
    if (Probe4Error(FileHandle) || !FileHandle || Probe4Error(FileHandle->Node) || !FileHandle->Node || Probe4Error(FileHandle->Node->Operations) || !FileHandle->Node->Operations)
    {
        ErrorOut_VFS_FSync(-EINVAL);
        return Error->ErrorCode;
    }

    if (Probe4Error(FileHandle->Node->Operations->Sync) || !FileHandle->Node->Operations->Sync)
    {
        return GeneralOK;
    }

    return FileHandle->Node->Operations->Sync(FileHandle->Node, Error);
}