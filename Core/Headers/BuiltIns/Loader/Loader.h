#pragma once

#include <__KCONF.h>
#include <Errors.h>

#include <Boot/PreBoot.h>

typedef struct LOADED_MODULE
{
    const char* Name;
    void* Address;
    uint64_t Size;
    struct LOADED_MODULE* Next; /*List*/
} LOADED_MODULE;

extern LOADED_MODULE* LoadedModules;

LOADED_MODULE* Loader_GetModules(SYSTEM_ERROR*);
LOADED_MODULE* Loader_FindModule(const char*, SYSTEM_ERROR*);
uint64_t Loader_GetModuleCount(SYSTEM_ERROR*);
