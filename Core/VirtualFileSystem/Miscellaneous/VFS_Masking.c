#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <DirtyHeap.h>

int
VFS_SetUnMask(long Mode, SYSTEM_ERROR* Error __UNUSED)
{
    UnMask = Mode;
    
    return GeneralOK;
}

long
VFS_GetUnMask(SYSTEM_ERROR* Error __UNUSED)
{
    return UnMask;
}