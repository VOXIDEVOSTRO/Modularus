#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_RegisterFileSystem(const FILESYSTEM_TYPE* FileSystemType, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_RegisterFileSystem(Code) \
        ErrorOut(Error, Code, FUNC_VFS_RegisterFileSystem)

    if (Probe4Error(FileSystemType) || !FileSystemType || Probe4Error(FileSystemType->Name) || !FileSystemType->Name || Probe4Error(FileSystemType->Mount) || !FileSystemType->Mount)
    {
        ErrorOut_VFS_RegisterFileSystem(-EINVAL);
        return Error->ErrorCode;
    }

    if (FileSystemCount >= MaxFileSystemTypes)
    {
        ErrorOut_VFS_RegisterFileSystem(-EOVERFLOW);
        return Error->ErrorCode;
    }

    for (long Iteration = 0; Iteration < FileSystemCount; Iteration++)
    {
        if (strcmp(FileSystemRegistry[Iteration]->Name, FileSystemType->Name) == 0)
        {
            ErrorOut_VFS_RegisterFileSystem(-EEXIST);
            return Error->ErrorCode;
        }
    }

    FileSystemRegistry[FileSystemCount++] = FileSystemType;

    return GeneralOK;
}

int
VFS_UnRegisterFileSystem(const char* Name, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_UnRegisterFileSystem(Code) \
        ErrorOut(Error, Code, FUNC_VFS_UnRegisterFileSystem)

    if (Probe4Error(Name) || !Name)
    {
        ErrorOut_VFS_UnRegisterFileSystem(-EINVAL);
        return Error->ErrorCode;
    }

    for (long Iteration = 0; Iteration < FileSystemCount; Iteration++)
    {
        if (strcmp(FileSystemRegistry[Iteration]->Name, Name) == 0)
        {
            for (long Index = Iteration; Index < FileSystemCount - 1; Index++)
            {
                FileSystemRegistry[Index] = FileSystemRegistry[Index + 1];
            }
            FileSystemRegistry[--FileSystemCount] = 0;
            return GeneralOK;
        }
    }

    ErrorOut_VFS_UnRegisterFileSystem(-ENOENT);
    return Error->ErrorCode;
}

const FILESYSTEM_TYPE*
VFS_FindFileSystem(const char* Name, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_FindFileSystem(Code) \
        ErrorOut(Error, Code, FUNC_VFS_FindFileSystem)

    if (Probe4Error(Name) || !Name)
    {
        ErrorOut_VFS_FindFileSystem(-EINVAL);
        return Error2Pointer(-EINVAL);
    }

    for (long Iteration = 0; Iteration < FileSystemCount; Iteration++)
    {
        if (strcmp(FileSystemRegistry[Iteration]->Name, Name) == 0)
        {
            return FileSystemRegistry[Iteration];
        }
    }

    ErrorOut_VFS_FindFileSystem(-ENOENT);
    return Error2Pointer(-ENOENT);
}

long
VfsListFs(const char** Output, long Capacity, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VfsListFs(Code) \
        ErrorOut(Error, Code, FUNC_VfsListFs)

    if (Probe4Error(Output) || !Output || Capacity <= 0)
    {
        ErrorOut_VfsListFs(-EINVAL);
        return Error->ErrorCode;
    }

    long Index = (FileSystemCount < Capacity) ? FileSystemCount : Capacity;
    for (long Iteration = 0; Iteration < Index; Iteration++)
    {
        Output[Iteration] = FileSystemRegistry[Iteration]->Name;
    }

    return Index;
}
