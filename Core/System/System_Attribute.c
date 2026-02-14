#include <System.h>
#include <VirtualFileSystem.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

int
System_GetAttribute(SYSTEM_NODE* Node, VFS_STAT* Stat, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_GetAttribute(Code) \
        ErrorOut(Error, Code, FUNC_System_GetAttribute)

    if (Probe4Error(Node) || !Node || Probe4Error(Stat) || !Stat)
    {
        ErrorOut_System_GetAttribute(-EINVAL);
        return Error->ErrorCode;
    }
    
    Stat->Inode = (long)Node;
    Stat->Size = Node->ContextSize;
    Stat->Blocks = 0;
    Stat->BlockSize = 4096;
    Stat->NumberOfLinks = 1;
    Stat->RawDevice = 0;
    Stat->Device = 0;
    Stat->Flags = 0;
    Stat->Type = (Node->Type == SystemNodeTypeEnumeration_DIRECTORY) ? VFSNode_DIRECTORY : VFSNode_FILE;
    Stat->Permission.Mode = Node->Mode;
    Stat->Permission.UserID = Node->UserID;
    Stat->Permission.GroupID = Node->GroupID;
    
    return GeneralOK;
}

int
System_SetAttribute(SYSTEM_NODE* Node, const VFS_STAT* Stat, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_SetAttribute(Code) \
        ErrorOut(Error, Code, FUNC_System_SetAttribute)

    if (Probe4Error(Node) || !Node || Probe4Error(Stat) || !Stat)
    {
        ErrorOut_System_SetAttribute(-EINVAL);
        return Error->ErrorCode;
    }
    
    ErrorOut_System_SetAttribute(-EROFS);
    return Error->ErrorCode;
}