#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <StaticPool.h>

int
VfsPruneCaches(SYSTEM_ERROR* Error UNUSED)
{
    return GeneralOK;
}

int
VfsSetDirCacheLimit(long Value, SYSTEM_ERROR* Error UNUSED)
{   
    DirectoryCacheLimit = Value;
    
    return GeneralOK;
}

long
VfsGetDirCacheLimit(SYSTEM_ERROR* Error UNUSED)
{
    return DirectoryCacheLimit;
}

int
VfsSetFileCacheLimit(long Value, SYSTEM_ERROR* Error UNUSED)
{
    FileCacheLimit = Value;
    
    return GeneralOK;
}

long
VfsGetFileCacheLimit(SYSTEM_ERROR* Error UNUSED)
{
    return FileCacheLimit;
}

int
VfsSetIoBlockSize(long Value, SYSTEM_ERROR* Error UNUSED)
{
    IOBlockSize = Value;
    
    return GeneralOK;
}

long
VfsGetIoBlockSize(SYSTEM_ERROR* Error UNUSED)
{
    return IOBlockSize;
}