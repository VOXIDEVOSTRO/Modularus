
#include <System.h>
#include <VirtualFileSystem.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

int
System_Open(VFS_NODE* VFSNode, FILE* File, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_Open(Code) \
        ErrorOut(Error, NULL, Code, FUNC_System_Open)

    if (Probe4Error(VFSNode) || !VFSNode || Probe4Error(File) || !File)
    {
        ErrorOut_System_Open(-EINVAL);
        return Error->ErrorCode;
    }
    
    SYSTEM_NODE* Node = (SYSTEM_NODE*)VFSNode->Private;
    
    if (Probe4Error(Node) || !Node)
    {
        ErrorOut_System_Open(-ENOENT);
        return Error->ErrorCode;
    }
    
    if (FileAllocatedCount >= MaxSystemFiles)
    {
        ErrorOut_System_Open(-ENFILE);
        return Error->ErrorCode;
    }
    
    SYSTEM_FILE* SystemFile = &FilePool[FileAllocatedCount++];
    memset(SystemFile, 0, sizeof(SYSTEM_FILE));
    
    SystemFile->Node = Node;
    SystemFile->Offset = 0;
    SystemFile->Flags = 0;
    SystemFile->ReferenceCount = 1;
    
    File->Private = SystemFile;
    
    if (Node->Operations && Node->Operations->Open)
    {
        return Node->Operations->Open(Node, SystemFile, Error);
    }
    
    return GeneralOK;
}

int
System_Close(FILE* File, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_Close(Code) \
        ErrorOut(Error, NULL, Code, FUNC_System_Close)

    if (Probe4Error(File) || !File)
    {
        ErrorOut_System_Close(-EINVAL);
        return Error->ErrorCode;
    }
    
    SYSTEM_FILE* SystemFile = (SYSTEM_FILE*)File->Private;
    
    if (Probe4Error(SystemFile) || !SystemFile)
    {
        ErrorOut_System_Close(-EBADF);
        return Error->ErrorCode;
    }
    
    memset(SystemFile, 0, sizeof(SYSTEM_FILE));
    FileAllocatedCount--;
    
    return GeneralOK;
}

long
System_Read(FILE* File, void* Buffer, long Size, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_Read(Code) \
        ErrorOut(Error, NULL, Code, FUNC_System_Read)

    if (Probe4Error(File) || !File || Probe4Error(Buffer) || !Buffer)
    {
        ErrorOut_System_Read(-EINVAL);
        return Error->ErrorCode;
    }
    
    SYSTEM_FILE* SystemFile = (SYSTEM_FILE*)File->Private;
    
    if (Probe4Error(SystemFile) || !SystemFile || Probe4Error(SystemFile->Node) || !SystemFile->Node)
    {
        ErrorOut_System_Read(-EBADF);
        return Error->ErrorCode;
    }
    
    SYSTEM_NODE* Node = SystemFile->Node;
    
    if (Node->Operations && Node->Operations->Read)
    {
        return Node->Operations->Read(SystemFile, Buffer, Size, Error);
    }
    
    if (Probe4Error(Node->Context) || !Node->Context)
    {
        ErrorOut_System_Read(-ENOENT);
        return Error->ErrorCode;
    }
    
    long Available = Node->ContextSize - SystemFile->Offset;
    
    if (Size > Available)
    {
        Size = Available;
    }
    
    if (Size > 0)
    {
        memcpy(Buffer, (char*)Node->Context + SystemFile->Offset, Size);
        SystemFile->Offset += Size;
    }
    
    return Size;
}

long
System_Write(FILE* File, const void* Buffer, long Size, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_Write(Code) \
        ErrorOut(Error, NULL, Code, FUNC_System_Write)

    if (Probe4Error(File) || !File || Probe4Error(Buffer) || !Buffer)
    {
        ErrorOut_System_Write(-EINVAL);
        return Error->ErrorCode;
    }
    
    SYSTEM_FILE* SystemFile = (SYSTEM_FILE*)File->Private;
    
    if (Probe4Error(SystemFile) || !SystemFile || Probe4Error(SystemFile->Node) || !SystemFile->Node)
    {
        ErrorOut_System_Write(-EBADF);
        return Error->ErrorCode;
    }
    
    SYSTEM_NODE* Node = SystemFile->Node;
    
    if (Node->Operations && Node->Operations->Write)
    {
        return Node->Operations->Write(SystemFile, Buffer, Size, Error);
    }
    
    ErrorOut_System_Write(-EROFS);
    return Error->ErrorCode;
}

int
System_Ioctl(FILE* File, uint64_t Request, void* Arguments, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_Ioctl(Code) \
        ErrorOut(Error, NULL, Code, FUNC_System_Ioctl)

    SYSTEM_FILE* SystemFile = (SYSTEM_FILE*)File->Private;
    if (Probe4Error(SystemFile) || !SystemFile || Probe4Error(SystemFile->Node) || !SystemFile->Node)
    {
        ErrorOut_System_Ioctl(-EINVAL);
        return Error->ErrorCode;
    }

    SYSTEM_NODE* Node = SystemFile->Node;
    
    if (Node->Operations && Node->Operations->Ioctl)
    {
        return Node->Operations->Ioctl(SystemFile, Request, Arguments, Error);
    }

    ErrorOut_System_Ioctl(-ENOENT);
    return Error->ErrorCode;
}
