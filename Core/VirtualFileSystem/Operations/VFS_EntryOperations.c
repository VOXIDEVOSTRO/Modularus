#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_Create(const char* Path, long Flags, VFS_PERMISSIONS Permission, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_Create(Code) \
        ErrorOut(Error, NULL, Code, FUNC_VFS_Create)

    DIRECTORY_ENTRY* Parent = 0;
    char Name[256];
    if (Probe4Error(Path) || !Path)
    {
        ErrorOut_VFS_Create(-EINVAL);
        return Error->ErrorCode;
    }

    const char* PathComponent = Path;
    if (IsSeperator(*PathComponent, Error))
    {
        PathComponent = SkipSeperator(PathComponent, Error);
    }

    VFS_NODE* Current = RootNode;
    DIRECTORY_ENTRY* DirectoryEntry = RootDirectoryEntry;
    while (*PathComponent)
    {
        long Index = NextCompare(PathComponent, Name, sizeof(Name), Error);
        if (Index <= 0)
        {
            break;
        }

        while (*PathComponent && !IsSeperator(*PathComponent, Error))
        {
            PathComponent++;
        }

        PathComponent = SkipSeperator(PathComponent, Error);
        Parent = DirectoryEntry;
        if (*PathComponent == 0)
        {
            break;
        }

        if (Probe4Error(Current) || !Current || Probe4Error(Current->Operations) || !Current->Operations || Probe4Error(Current->Operations->Lookup) || !Current->Operations->Lookup)
        {
            ErrorOut_VFS_Create(-ENOSYS);
            return Error->ErrorCode;
        }

        VFS_NODE* Next = Current->Operations->Lookup(Current, Name, Error);
        if (Probe4Error(Next) || !Next)
        {
            ErrorOut_VFS_Create(-ENOENT);
            return Error->ErrorCode;
        }

        char* Dublicate = (char*)KMalloc((size_t)(Index + 1), Error);
        if (Probe4Error(Dublicate) || !Dublicate)
        {
            ErrorOut_VFS_Create(-ENOMEM);
            return Error->ErrorCode;
        }

        memcpy(Dublicate, Name, (size_t)(Index + 1));
        DirectoryEntry = AllocateDirectoryEntry(Dublicate, DirectoryEntry, Next, Error);
        if (Probe4Error(DirectoryEntry) || !DirectoryEntry)
        {
            ErrorOut_VFS_Create(Error->ErrorCode);
            return Error->ErrorCode;
        }

        Current = Next;
    }

    if (Probe4Error(Parent) || !Parent || Probe4Error(Parent->Node) || !Parent->Node || Probe4Error(Parent->Node->Operations) || !Parent->Node->Operations || Probe4Error(Parent->Node->Operations->Create) || !Parent->Node->Operations->Create)
    {
        ErrorOut_VFS_Create(-ENOSYS);
        return Error->ErrorCode;
    }
    
    return Parent->Node->Operations->Create(Parent->Node, Name, Flags, Permission, Error);
}

int
VFS_UnLink(const char* Path, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_UnLink(Code) \
        ErrorOut(Error, NULL, Code, FUNC_VFS_UnLink)

    DIRECTORY_ENTRY* Base = NULL;
    char Name[256];

    if (Probe4Error(Path) || !Path)
    {
        ErrorOut_VFS_UnLink(-EINVAL);
        return Error->ErrorCode;
    }

    const char* PathComponent = Path;
    if (IsSeperator(*PathComponent, Error))
    {
        Path = SkipSeperator(PathComponent, Error);
    }

    VFS_NODE*  Current = RootNode;
    DIRECTORY_ENTRY* DirectoryEntry = RootDirectoryEntry;
    while (*PathComponent)
    {
        long Index = NextCompare(PathComponent, Name, sizeof(Name), Error);
        if (Index <= 0)
        {
            break;
        }

        while (*PathComponent && !IsSeperator(*PathComponent, Error))
        {
            PathComponent++;
        }

        PathComponent = SkipSeperator(PathComponent, Error);
        if (*PathComponent == 0)
        {
            Base = DirectoryEntry;
            break;
        }

        if (Probe4Error(Current) || !Current || Probe4Error(Current->Operations) || !Current->Operations || Probe4Error(Current->Operations->Lookup) || !Current->Operations->Lookup)
        {
            ErrorOut_VFS_UnLink(-ENOSYS);
            return Error->ErrorCode;
        }

        VFS_NODE* Next = Current->Operations->Lookup(Current, Name, Error);
        if (Probe4Error(Next) || !Next)
        {
            ErrorOut_VFS_UnLink(-ENOENT);
            return Error->ErrorCode;
        }
        
        char* Dublicate = (char*)KMalloc((size_t)(Index + 1), Error);
        if (Probe4Error(Dublicate) || !Dublicate)
        {
            ErrorOut_VFS_UnLink(-ENOMEM);
            return Error->ErrorCode;
        }

        memcpy(Dublicate, Name, (size_t)(Index + 1));
        DirectoryEntry = AllocateDirectoryEntry(Dublicate, DirectoryEntry, Next, Error);
        if (Probe4Error(DirectoryEntry) || !DirectoryEntry)
        {
            ErrorOut_VFS_UnLink(Error->ErrorCode);
            return Error->ErrorCode;
        }

        Current = Next;
    }

    if (Probe4Error(Base) || !Base || Probe4Error(Base->Node) || !Base->Node || Probe4Error(Base->Node->Operations) || !Base->Node->Operations || Probe4Error(Base->Node->Operations->Unlink) || !Base->Node->Operations->Unlink)
    {
        ErrorOut_VFS_UnLink(-ENOSYS);
        return Error->ErrorCode;
    }
    
    return Base->Node->Operations->Unlink(Base->Node, Name, Error);
}
