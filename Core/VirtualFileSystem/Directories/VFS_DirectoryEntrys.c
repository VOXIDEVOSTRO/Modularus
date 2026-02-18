#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_DentryInvalidate(DIRECTORY_ENTRY* DirectoryEntry, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_DentryInvalidate(Code) \
        ErrorOut(Error, Code, FUNC_VFS_DentryInvalidate)
    
    if (Probe4Error(DirectoryEntry) || !DirectoryEntry)
    {
        ErrorOut_VFS_DentryInvalidate(-EINVAL);
        return Error->ErrorCode;
    }

    DirectoryEntry->Flags |= 1;
    
    return GeneralOK;
}

int
VFS_DentryRevalidate(DIRECTORY_ENTRY* DirectoryEntry, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_DentryRevalidate(Code) \
        ErrorOut(Error, Code, FUNC_VFS_DentryRevalidate)

    if (Probe4Error(DirectoryEntry) || !DirectoryEntry)
    {
        ErrorOut_VFS_DentryRevalidate(-EINVAL);
        return Error->ErrorCode;
    }

    DirectoryEntry->Flags &= ~1;
    
    return GeneralOK;
}

int
VFS_DentryAttach(DIRECTORY_ENTRY* DirectoryEntry, VFS_NODE* Node, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_DentryAttach(Code) \
        ErrorOut(Error, Code, FUNC_VFS_DentryAttach)

    if (Probe4Error(DirectoryEntry) || !DirectoryEntry || Probe4Error(Node) || !Node)
    {
        ErrorOut_VFS_DentryAttach(-EINVAL);
        return Error->ErrorCode;
    }

    DirectoryEntry->Node = Node;
    
    return GeneralOK;
}

int
VFS_DentryDetach(DIRECTORY_ENTRY* DirectoryEntry, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_DentryDetach(Code) \
        ErrorOut(Error, Code, FUNC_VFS_DentryDetach)

    if (Probe4Error(DirectoryEntry) || !DirectoryEntry)
    {
        ErrorOut_VFS_DentryDetach(-EINVAL);
        return Error->ErrorCode;
    }

    DirectoryEntry->Node = NULL;
    
    return GeneralOK;
}

int
VFS_DentryName(DIRECTORY_ENTRY* DirectoryEntry, char* Buffer, long Length, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_DentryName(Code) \
        ErrorOut(Error, Code, FUNC_VFS_DentryName)

    if (Probe4Error(DirectoryEntry) || !DirectoryEntry || Probe4Error(Buffer) || !Buffer || Length <= 0)
    {
        ErrorOut_VFS_DentryName(-EINVAL);
        return Error->ErrorCode;
    }

    long Index = (long)strlen(DirectoryEntry->Name);
    if (Index >= Length)
    {
        ErrorOut_VFS_DentryName(-ENAMETOOLONG);
        return Error->ErrorCode;
    }

    memcpy(Buffer, DirectoryEntry->Name, (size_t)(Index + 1));
    
    return GeneralOK;
}
