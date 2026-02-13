#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_SetFlag(const char* Path __UNUSED, long __Flag__ __UNUSED, SYSTEM_ERROR* Error __UNUSED)
{
    return GeneralOK;
}

int
VFS_ClearFlag(const char* Path __UNUSED, long __Flag__ __UNUSED, SYSTEM_ERROR* Error __UNUSED)
{
    return GeneralOK;
}

long
VFS_GetFlags(const char* Path __UNUSED, SYSTEM_ERROR* Error __UNUSED)
{
    return GeneralOK;
}
