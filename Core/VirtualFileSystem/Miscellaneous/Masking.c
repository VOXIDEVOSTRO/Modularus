#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <StaticPool.h>

int
VfsSetUmask(long Mode, SYSTEM_ERROR* Error UNUSED)
{
    UnMask = Mode;
    
    return GeneralOK;
}

long
VfsGetUmask(SYSTEM_ERROR* Error UNUSED)
{
    return UnMask;
}