#include <System.h>
#include <VirtualFileSystem.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

SYSTEM_NODE* SystemRoot = 0;
SYSTEM_FILESYSTEM_INSTANCE* SystemInstance = 0;
SYSTEM_NODE* NodePool = 0;
uint64_t NodeAllocatedCount = 0;
SYSTEM_FILE* FilePool = 0;
uint64_t FileAllocatedCount = 0;
const uint64_t MaxSystemNodes = 1024;
const uint64_t MaxSystemFiles = 256;

int
System_KickStart(SYSTEM_ERROR* Error)
{
    #define ErrorOut_System_KickStart(Code) \
        ErrorOut(Error, Code, FUNC_System_KickStart)

    NodeAllocatedCount = 0;
    FileAllocatedCount = 0;
    
    NodePool = KMalloc(MaxSystemNodes * sizeof(SYSTEM_NODE), Error);
    if (Probe4Error(NodePool) || !NodePool)
    {
        ErrorOut_System_KickStart(-ENOMEM);
        return Error->ErrorCode;
    }
    
    FilePool = KMalloc(MaxSystemFiles * sizeof(SYSTEM_FILE), Error);
    if (Probe4Error(FilePool) || !FilePool)
    {
        KFree(NodePool, Error);

        ErrorOut_System_KickStart(-ENOMEM);
        return Error->ErrorCode;
    }
    
    memset(NodePool, 0, MaxSystemNodes * sizeof(SYSTEM_NODE));
    memset(FilePool, 0, MaxSystemFiles * sizeof(SYSTEM_FILE));
    
    SystemInstance = KMalloc(sizeof(SYSTEM_FILESYSTEM_INSTANCE), Error);
    if (Probe4Error(SystemInstance) || !SystemInstance)
    {
        KFree(NodePool, Error);
        KFree(FilePool, Error);

        ErrorOut_System_KickStart(-ENOMEM);
        return Error->ErrorCode;
    }
    
    SystemInstance->SuperBlock = 0;
    SystemInstance->Root = 0;
    SystemInstance->NodeCount = 0;
    SystemInstance->FileCount = 0;
    
    SystemRoot = System_CreateDirectory("/", Error);
    if (Probe4Error(SystemRoot) || !SystemRoot)
    {
        ErrorOut_System_KickStart(Error->ErrorCode);
        return Error->ErrorCode;
    }
    
    int Result = System_RegisterFileSystem(Error);
    if (Result != GeneralOK)
    {
        ErrorOut_System_KickStart(Result);
        return Result;
    }
    
    return GeneralOK;
}

int
System_PowerOff(SYSTEM_ERROR* Error)
{
    System_UnRegisterFileSystem(Error);
    
    if (SystemInstance)
    {
        KFree(SystemInstance, Error);
        SystemInstance = 0;
    }
    
    if (FilePool)
    {
        KFree(FilePool, Error);
        FilePool = 0;
    }
    
    if (NodePool)
    {
        KFree(NodePool, Error);
        NodePool = 0;
    }
    
    SystemRoot = 0;
    NodeAllocatedCount = 0;
    FileAllocatedCount = 0;
    
    return GeneralOK;
}
