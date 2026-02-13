#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_PruneCaches(SYSTEM_ERROR* Error __UNUSED)
{
    return GeneralOK;
}

int
VFS_SetDirectoryCacheLimit(long Value, SYSTEM_ERROR* Error __UNUSED)
{   
    DirectoryCacheLimit = Value;
    
    return GeneralOK;
}

long
VFS_GetDirectoryCacheLimit(SYSTEM_ERROR* Error __UNUSED)
{
    return DirectoryCacheLimit;
}

int
VFS_SetFileCacheLimit(long Value, SYSTEM_ERROR* Error __UNUSED)
{
    FileCacheLimit = Value;
    
    return GeneralOK;
}

long
VFS_GetFileCacheLimit(SYSTEM_ERROR* Error __UNUSED)
{
    return FileCacheLimit;
}

int
VFS_SetIOBlockSize(long Value, SYSTEM_ERROR* Error __UNUSED)
{
    IOBlockSize = Value;
    
    return GeneralOK;
}

long
VFS_GetIOBlockSize(SYSTEM_ERROR* Error __UNUSED)
{
    return IOBlockSize;
}