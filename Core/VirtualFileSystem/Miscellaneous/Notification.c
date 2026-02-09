#include <KernelCLibrary.h>
#include <VirtualFileSystem.h>
#include <__KCONF.h>
#include <StaticPool.h>

int
VfsNotifySubscribe(const char* Path UNUSED, long __Mask__ UNUSED, SYSTEM_ERROR* UNUSED)
{
    return GeneralOK;
}

int
VfsNotifyUnsubscribe(const char* Path UNUSED, SYSTEM_ERROR* Error UNUSED)
{
    return GeneralOK;
}

int
VfsNotifyPoll(const char* Path UNUSED, long* OutMask, SYSTEM_ERROR* Error)
{
    #define ErrorOut_VfsNotifyPoll(Code) \
        ErrorOut(Error, Code, FUNC_VfsNotifyPoll)

    if (Probe4Error(OutMask) || !OutMask)
    {
        ErrorOut_VfsNotifyPoll(-EINVAL);
        return -EINVAL;
    }

    *OutMask = 0;
    
    return GeneralOK;
}