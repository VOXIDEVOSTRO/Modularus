#include <__KCONF.h>
#include <StaticPool.h>

uint8_t Pool[64 * 1024 * 1024];  /* 64 MB pool */
uint8_t* Pointer = Pool;
uint8_t* Ending = Pool + sizeof(Pool);

void* KMalloc(uint64_t Size, SYSTEM_ERROR* Error)
{
    Size = (Size + 7) & ~7;
    
    if(Pointer + Size > Ending)
    {
        ErrorOut(Error, -ENOMEM, General);
        return Error2Pointer(-ENOMEM);
    }

    void* Pointer = Pointer;
    Pointer += Size;

    return Pointer;
}

void KFree(void* Pointer UNUSED, SYSTEM_ERROR* Error UNUSED)
{
    /* No-op */
}