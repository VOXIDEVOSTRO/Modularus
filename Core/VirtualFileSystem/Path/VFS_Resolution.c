#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

DIRECTORY_ENTRY*
VFS_Resolve(const char* Path, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_Resolve(Code) \
        ErrorOut(Error, Code, FUNC_VFS_Resolve)

    if (Probe4Error(Path) || !Path)
    {
        ErrorOut_VFS_Resolve(-EINVAL);
        return Error2Pointer(Error->ErrorCode);
    }

    if (Probe4Error(RootNode) || !RootNode)
    {
        ErrorOut_VFS_Resolve(-ENOENT);
        return Error2Pointer(Error->ErrorCode);
    }

    if (strcmp(Path, "/") == 0)
    {
        return RootDirectoryEntry;
    }

    MOUNT_ENTRY* MountEntry = FindMount(Path, Error);
    if (Probe4Error(MountEntry) || !MountEntry)
    {
        return Walk(RootNode, RootDirectoryEntry, Path, Error);
    }

    const char* MountPoint = MountEntry->Path;
    long        MountLength = (long)strlen(MountPoint);

    if (strncmp(Path, MountPoint, (size_t)MountLength) == 0 && Path[MountLength] == '\0')
    {
        DIRECTORY_ENTRY* DirectoryEntry = AllocateDirectoryEntry(MountPoint, RootDirectoryEntry, MountEntry->SuperBlock->Root, Error);
        if(Probe4Error(DirectoryEntry) || !DirectoryEntry)
        {
            ErrorOut_VFS_Resolve(-ENOENT);
            return Error2Pointer(Error->ErrorCode);
        }
        else
        {
            return DirectoryEntry;
        }
    }

    const char* Tail = Path + MountLength;
    while (*Tail == '/')
    {
        Tail++;
    }

    if (!*Tail)
    {
        DIRECTORY_ENTRY* DirectoryEntry = AllocateDirectoryEntry(MountPoint, RootDirectoryEntry, MountEntry->SuperBlock->Root, Error);
        if(Probe4Error(DirectoryEntry) || !DirectoryEntry)
        {
            ErrorOut_VFS_Resolve(-ENOENT);
            return Error2Pointer(Error->ErrorCode);
        }
        else
        {
            return DirectoryEntry;
        }
    }

    return Walk(MountEntry->SuperBlock->Root, RootDirectoryEntry, Tail, Error);
}

DIRECTORY_ENTRY*
VFS_ResolveAt(DIRECTORY_ENTRY* Base, const char* ResolvePath, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_ResolveAt(Code) \
        ErrorOut(Error, Code, FUNC_VFS_ResolveAt)

    if (Probe4Error(Base) || !Base || Probe4Error(Base->Node) || !Base->Node || Probe4Error(ResolvePath) || !ResolvePath)
    {
        ErrorOut_VFS_ResolveAt(-EINVAL);
        return Error2Pointer(Error->ErrorCode);
    }

    if (!*ResolvePath)
    {
        return Base;
    }

    if (IsSeperator(*ResolvePath, Error))
    {
        return VFS_Resolve(ResolvePath, Error);
    }

    return Walk(Base->Node, Base, ResolvePath, Error);
}

VFS_NODE*
VFS_LookUp(DIRECTORY_ENTRY* Base, const char* Name, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_LookUp(Code) \
        ErrorOut(Error, Code, FUNC_VFS_LookUp)

    if (Probe4Error(Base) || !Base || Probe4Error(Base->Node) || !Base->Node || Probe4Error(Name) || !Name)
    {
        ErrorOut_VFS_LookUp(-EINVAL);
        return Error2Pointer(Error->ErrorCode);
    }

    if (Probe4Error(Base->Node->Operations) || !Base->Node->Operations || Probe4Error(Base->Node->Operations->Lookup) || !Base->Node->Operations->Lookup)
    {
        ErrorOut_VFS_LookUp(-ENOSYS);
        return Error2Pointer(Error->ErrorCode);
    }

    return Base->Node->Operations->Lookup(Base->Node, Name, Error);
}
