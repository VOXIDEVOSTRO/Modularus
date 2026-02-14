#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

FILE*
VFS_Open(const char* Path, long Flags, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_Open(Code) \
        ErrorOut(Error, Code, FUNC_VFS_Open)

    DIRECTORY_ENTRY* DirectoryEntry = VFS_Resolve(Path, Error);
    if (Probe4Error(DirectoryEntry) || !DirectoryEntry || Probe4Error(DirectoryEntry->Node) || !DirectoryEntry->Node)
    {
        ErrorOut_VFS_Open(-ENOENT);
        return Error2Pointer(-ENOENT);
    }

    if (Probe4Error(DirectoryEntry->Node->Operations) || !DirectoryEntry->Node->Operations || Probe4Error(DirectoryEntry->Node->Operations->Open) || !DirectoryEntry->Node->Operations->Open)
    {
        ErrorOut_VFS_Open(-ENOSYS);
        return Error2Pointer(-ENOSYS);
    }

    FILE* FileHandle = (FILE*)KMalloc(sizeof(FILE), Error);
    if (Probe4Error(FileHandle) || !FileHandle)
    {
        ErrorOut_VFS_Open(-ENOMEM);
        return Error2Pointer(-ENOMEM);
    }

    FileHandle->Node = DirectoryEntry->Node;
    FileHandle->Offset = 0;
    FileHandle->Flags = Flags;
    FileHandle->ReferenceCount = 1;
    FileHandle->Private = 0;

    if (DirectoryEntry->Node->Operations->Open(DirectoryEntry->Node, FileHandle, Error) != GeneralOK)
    {
        KFree(FileHandle, Error);

        ErrorOut_VFS_Open(Error->ErrorCode);
        return Error2Pointer(Error->ErrorCode);
    }

    return FileHandle;
}

int
VFS_Close(FILE* FileHandle, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_Close(Code) \
        ErrorOut(Error, Code, FUNC_VFS_Close)

    if (Probe4Error(FileHandle) || !FileHandle)
    {
        ErrorOut_VFS_Close(-EINVAL);
        return Error->ErrorCode;
    }

    if (FileHandle->Node && FileHandle->Node->Operations && FileHandle->Node->Operations->Close)
    {
        FileHandle->Node->Operations->Close(FileHandle, Error);
    }

    KFree(FileHandle, Error);
    
    return GeneralOK;
}

long
VFS_Read(FILE* FileHandle, void* OutputBuffer, long BufferLength, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_Read(Code) \
        ErrorOut(Error, Code, FUNC_VFS_Read)
    
    if (Probe4Error(FileHandle) || !FileHandle || Probe4Error(OutputBuffer) || !OutputBuffer || BufferLength <= 0)
    {
        ErrorOut_VFS_Read(-EINVAL);
        return Error->ErrorCode;
    }

    if (Probe4Error(FileHandle->Node) || !FileHandle->Node || Probe4Error(FileHandle->Node->Operations) || !FileHandle->Node->Operations || Probe4Error(FileHandle->Node->Operations->Read) || !FileHandle->Node->Operations->Read)
    {
        ErrorOut_VFS_Read(-ENOSYS);
        return Error->ErrorCode;
    }

    long BytesRead = FileHandle->Node->Operations->Read(FileHandle, OutputBuffer, BufferLength, Error);
    if (BytesRead > 0)
    {
        FileHandle->Offset += BytesRead;
    }
    
    return BytesRead;
}

long
VFS_Write(FILE* FileHandle, const void* InputBuffer, long BufferLength, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_Write(Code) \
        ErrorOut(Error, Code, FUNC_VFS_Write)
    
    if (Probe4Error(FileHandle) || !FileHandle || Probe4Error(InputBuffer) || !InputBuffer || BufferLength <= 0)
    {
        ErrorOut_VFS_Write(-EINVAL);
        return Error->ErrorCode;
    }

    if (Probe4Error(FileHandle->Node) || !FileHandle->Node || Probe4Error(FileHandle->Node->Operations) || !FileHandle->Node->Operations || Probe4Error(FileHandle->Node->Operations->Write) || !FileHandle->Node->Operations->Write)
    {
        ErrorOut_VFS_Write(-ENOSYS);
        return Error->ErrorCode;
    }

    long BytesWritten = FileHandle->Node->Operations->Write(FileHandle, InputBuffer, BufferLength, Error);
    if (BytesWritten > 0)
    {
        FileHandle->Offset += BytesWritten;
    }
    
    return BytesWritten;
}

FILE*
VFS_OpenAt(DIRECTORY_ENTRY* BaseDirectory, const char* ResolvePath, long Flags, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_OpenAt(Code) \
        ErrorOut(Error, Code, FUNC_VFS_OpenAt)
    
    DIRECTORY_ENTRY* DirectoryEntry = VFS_ResolveAt(BaseDirectory, ResolvePath, Error);
    if (Probe4Error(DirectoryEntry) || !DirectoryEntry || Probe4Error(DirectoryEntry->Node) || !DirectoryEntry->Node)
    {
        ErrorOut_VFS_OpenAt(-ENOENT);
        return Error2Pointer(-ENOENT);
    }

    if (Probe4Error(DirectoryEntry->Node->Operations) || !DirectoryEntry->Node->Operations || Probe4Error(DirectoryEntry->Node->Operations->Open) ||
        !DirectoryEntry->Node->Operations->Open)
    {
        ErrorOut_VFS_OpenAt(-ENOSYS);
        return Error2Pointer(-ENOSYS);
    }

    FILE* FileHandle = (FILE*)KMalloc(sizeof(FILE), Error);
    if (Probe4Error(FileHandle) || !FileHandle)
    {
        ErrorOut_VFS_OpenAt(-ENOMEM);
        return Error2Pointer(-ENOMEM);
    }

    FileHandle->Node = DirectoryEntry->Node;
    FileHandle->Offset = 0;
    FileHandle->Flags = Flags;
    FileHandle->ReferenceCount = 1;
    FileHandle->Private = 0;

    if (DirectoryEntry->Node->Operations->Open(DirectoryEntry->Node, FileHandle, Error) != GeneralOK)
    {
        KFree(FileHandle, Error);

        ErrorOut_VFS_OpenAt(Error->ErrorCode);
        return Error2Pointer(Error->ErrorCode);
    }

    return FileHandle;
}

long
VFS_LSeek(FILE* FileHandle, long Offset, int Whence, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_LSeek(Code) \
        ErrorOut(Error, Code, FUNC_VFS_LSeek)
    
    if (Probe4Error(FileHandle) || !FileHandle)
    {
        ErrorOut_VFS_LSeek(-EINVAL);
        return Error->ErrorCode;
    }

    if (Probe4Error(FileHandle->Node) || !FileHandle->Node || Probe4Error(FileHandle->Node->Operations) || !FileHandle->Node->Operations || Probe4Error(FileHandle->Node->Operations->Lseek) || !FileHandle->Node->Operations->Lseek)
    {
        ErrorOut_VFS_LSeek(-ENOSYS);
        return Error->ErrorCode;
    }

    long NewOffset = FileHandle->Node->Operations->Lseek(FileHandle, Offset, Whence, Error);
    if (NewOffset >= 0)
    {
        FileHandle->Offset = NewOffset;
    }
    
    return NewOffset;
}

int
VFS_IOControl(FILE* FileHandle, uint64_t Command, void* Argument, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VFS_IOControl(Code) \
        ErrorOut(Error, Code, FUNC_VFS_IOControl)
    
    if (Probe4Error(FileHandle) || !FileHandle)
    {
        ErrorOut_VFS_IOControl(-EINVAL);
        return Error->ErrorCode;
    }

    if (Probe4Error(FileHandle->Node) || !FileHandle->Node || Probe4Error(FileHandle->Node->Operations) || !FileHandle->Node->Operations || Probe4Error(FileHandle->Node->Operations->Ioctl) || !FileHandle->Node->Operations->Ioctl)
    {
        ErrorOut_VFS_IOControl(-ENOSYS);
        return Error->ErrorCode;
    }

    return FileHandle->Node->Operations->Ioctl(FileHandle, Command, Argument, Error);
}