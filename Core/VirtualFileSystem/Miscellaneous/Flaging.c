#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <StaticPool.h>

int
VfsSetFlag(const char* Path UNUSED, long __Flag__ UNUSED, SYSTEM_ERROR* Error UNUSED)
{
    return GeneralOK;
}

int
VfsClearFlag(const char* Path UNUSED, long __Flag__ UNUSED, SYSTEM_ERROR* Error UNUSED)
{
    return GeneralOK;
}

long
VfsGetFlags(const char* Path UNUSED, SYSTEM_ERROR* Error UNUSED)
{
    return GeneralOK;
}
