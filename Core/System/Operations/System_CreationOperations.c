#include <System.h>
#include <VirtualFileSystem.h>
#include <DirtyHeap.h>
#include <KernelCLibrary.h>

SYSTEM_NODE*
System_CreateFile(const char* Name, const SYSTEM_OPERATIONS* Operations, void* Context, uint64_t ContextSize, SYSTEM_ERROR* Error)
{
    return System_CreateNode(Name, SystemNodeTypeEnumeration_FILE, Operations, Context, ContextSize, Error);
}

SYSTEM_NODE*
System_CreateDirectory(const char* Name, SYSTEM_ERROR* Error)
{
    return System_CreateNode(Name, SystemNodeTypeEnumeration_DIRECTORY, 0, 0, 0, Error);
}