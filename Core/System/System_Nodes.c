#include <System.h>
#include <VirtualFileSystem.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

SYSTEM_NODE*
System_CreateNode(const char* Name, SYSTEM_NODE_TYPE_ENUMERATION Type, const SYSTEM_OPERATIONS* Operations, void* Context, uint64_t ContextSize, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_CreateNode(Code) \
        ErrorOut(Error, Code, FUNC_System_CreateNode)

    if (NodeAllocatedCount >= MaxSystemNodes)
    {
        ErrorOut_System_CreateNode(-ENOSPC);
        return Error2Pointer(Error->ErrorCode);
    }
    
    SYSTEM_NODE* Node = &NodePool[NodeAllocatedCount++];
    memset(Node, 0, sizeof(SYSTEM_NODE));
    
    Node->Name = Name;
    Node->Type = Type;
    Node->Operations = Operations;
    Node->Context = Context;
    Node->ContextSize = ContextSize;
    Node->Mode = 0644;
    Node->UserID = 0;
    Node->GroupID = 0;
    Node->ReferenceCount = 1;
    
    if (SystemInstance)
    {
        SystemInstance->NodeCount++;
    }
    
    return Node;
}

int
System_DeleteNode(SYSTEM_NODE* Node, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_DeleteNode(Code) \
        ErrorOut(Error, Code, FUNC_System_DeleteNode)

    if (Probe4Error(Node) || !Node)
    {
        ErrorOut_System_DeleteNode(-EINVAL);
        return Error->ErrorCode;
    }
    
    if (Node->Parent)
    {
        SYSTEM_NODE* Child = Node->Parent->Child;
        SYSTEM_NODE* Previous = 0;
        
        while (Child)
        {
            if (Child == Node)
            {
                if (Previous)
                {
                    Previous->Next = Node->Next;
                }
                else
                {
                    Node->Parent->Child = Node->Next;
                }
                break;
            }
            Previous = Child;
            Child = Child->Next;
        }
    }
    
    memset(Node, 0, sizeof(SYSTEM_NODE));
    NodeAllocatedCount--;
    
    return GeneralOK;
}

SYSTEM_NODE*
System_FindNode(SYSTEM_NODE* Parent, const char* Name, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_FindNode(Code) \
        ErrorOut(Error, Code, FUNC_System_FindNode)

    if (Probe4Error(Parent) || !Parent || Probe4Error(Name) || !Name)
    {
        ErrorOut_System_FindNode(-EINVAL);
        return Error2Pointer(Error->ErrorCode);
    }
    
    SYSTEM_NODE* Child = Parent->Child;
    
    while (Child)
    {
        if (strcmp(Child->Name, Name) == 0)
        {
            return Child;
        }
        Child = Child->Next;
    }
    
    ErrorOut_System_FindNode(-EINVAL);
    return Error2Pointer(Error->ErrorCode);
}

int
System_AttachNode(SYSTEM_NODE* Parent, SYSTEM_NODE* Child, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_AttachNode(Code) \
        ErrorOut(Error, Code, FUNC_System_AttachNode)

    if (Probe4Error(Parent) || !Parent || Probe4Error(Child) || !Child)
    {
        ErrorOut_System_AttachNode(-EINVAL);
        return Error->ErrorCode;
    }
    
    Child->Parent = Parent;
    Child->Next = Parent->Child;
    Parent->Child = Child;
    
    return GeneralOK;
}

int
System_DetachNode(SYSTEM_NODE* Node, SYSTEM_ERROR* Error)
{
    return System_DeleteNode(Node, Error);
}

SYSTEM_NODE*
System_GetRoot(SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_GetRoot(Code) \
        ErrorOut(Error, Code, FUNC_System_GetRoot)

    if (Probe4Error(SystemRoot) || !SystemRoot)
    {
        ErrorOut_System_GetRoot(-ENOENT);
        return Error2Pointer(Error->ErrorCode);
    }
    
    return SystemRoot;
}