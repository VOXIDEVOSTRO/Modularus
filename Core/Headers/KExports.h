#pragma once

#include <__KCONF.h>
#include <Errors.h>

typedef struct KEXPORTS
{
    const char* Name;    /* Symbol name */
    void*       Address; /* Symbol address */
} KEXPORTS;

#define KEXPORT(Symbol)                        \
    __attribute__((used, section(".kexports")))\
    static const KEXPORTS _kexp_##Symbol=       \
    {                                          \
        #Symbol, (void*)&Symbol                \
    };                                         \

extern const KEXPORTS __start_kexports[];/*Linker script*/
extern const KEXPORTS __stop_kexports[];/*Linker script*/

void* LookUpKExport(const char*, SYSTEM_ERROR*);