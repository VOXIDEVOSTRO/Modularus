#include <System.h>
#include <VirtualFileSystem.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

int
System_SetContext(SYSTEM_NODE* Node, void* Context, uint64_t Size, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_SetContext(Code) \
        ErrorOut(Error, Code, FUNC_System_SetContext)

    if (Probe4Error(Node) || !Node)
    {
        ErrorOut_System_SetContext(-EINVAL);
        return Error->ErrorCode;
    }
    
    Node->Context = Context;
    Node->ContextSize = Size;
    
    return GeneralOK;
}

void*
System_GetContext(SYSTEM_NODE* Node, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_GetContext(Code) \
        ErrorOut(Error, Code, FUNC_System_GetContext)

    if (Probe4Error(Node) || !Node)
    {
        ErrorOut_System_GetContext(-EINVAL);
        return Error2Pointer(Error->ErrorCode);
    }
    
    return Node->Context;
}

uint64_t
System_GetContextSize(SYSTEM_NODE* Node, SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_GetContextSize(Code) \
        ErrorOut(Error, Code, FUNC_System_GetContextSize)

    if (Probe4Error(Node) || !Node)
    {
        ErrorOut_System_GetContextSize(-EINVAL);
        return 0; /*this is indeed a error*/
    }
    
    return Node->ContextSize;
}