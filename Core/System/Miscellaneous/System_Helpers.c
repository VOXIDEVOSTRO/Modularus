#include <System.h>
#include <VirtualFileSystem.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

VFS_NODE*
System_LookUp(VFS_NODE* VFSNode, const char* Name, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_LookUp(Code) \
        ErrorOut(Error, NULL, Code, FUNC_System_LookUp)

    if (Probe4Error(VFSNode) || !VFSNode || Probe4Error(Name) || !Name)
    {
        ErrorOut_System_LookUp(-EINVAL);
        return Error2Pointer(Error->ErrorCode);
    }
    
    SYSTEM_NODE* Node = (SYSTEM_NODE*)VFSNode->Private;
     
    if (Probe4Error(Node) || !Node)
    {
        ErrorOut_System_LookUp(-ENOENT);
        return Error2Pointer(Error->ErrorCode);
    }
    
    SYSTEM_NODE* Found = System_FindNode(Node, Name, Error);
    
    if (Probe4Error(Found) || !Found)
    {
        ErrorOut_System_LookUp(-ENOENT);
        return Error2Pointer(Error->ErrorCode);
    }
    
    VFS_NODE* NodeAllocationResult = KMalloc(sizeof(VFS_NODE), Error);
    
    if (Probe4Error(NodeAllocationResult) || !NodeAllocationResult)
    {
        ErrorOut_System_LookUp(-ENOMEM);
        return Error2Pointer(Error->ErrorCode);
    }
    
    NodeAllocationResult->Type = (Found->Type == SystemNodeTypeEnumeration_DIRECTORY) ? VFSNode_DIRECTORY : VFSNode_FILE;
    NodeAllocationResult->Private = Found;
    NodeAllocationResult->Operations = &SystemBasicOperations;
    NodeAllocationResult->ReferenceCount = 1;
    
    return NodeAllocationResult;
}

SYSTEM_NODE*
System_Walk(const char* Path, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_Walk(Code) \
        ErrorOut(Error, NULL, Code, FUNC_System_Walk)

    if (Probe4Error(Path) || !Path)
    {
        ErrorOut_System_Walk(-EINVAL);
        return Error2Pointer(Error->ErrorCode);
    }
    
    SYSTEM_NODE* Current = SystemRoot;
    const char* Component = Path;
    
    if (*Component == '/')
    {
        Component++;
    }
    
    while (*Component)
    {
        const char* End = Component;
        
        while (*End && *End != '/')
        {
            End++;
        }
        
        char Name[256];
        uint64_t Length = End - Component;
        
        if (Length >= sizeof(Name))
        {
            ErrorOut_System_Walk(-ENAMETOOLONG);
            return Error2Pointer(Error->ErrorCode);
        }
        
        memcpy(Name, Component, Length);
        Name[Length] = 0;
        
        Current = System_FindNode(Current, Name, Error);
        
        if (Probe4Error(Current) || !Current)
        {
            ErrorOut_System_Walk(-ENOENT);
            return Error2Pointer(Error->ErrorCode);
        }
        
        Component = End;
        
        if (*Component == '/')
        {
            Component++;
        }
    }
    
    return Current;
}
