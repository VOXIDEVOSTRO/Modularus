#pragma once

#include <__KCONF.h>
#include <Errors.h>

#include <System.h>
#include <Boot/PreBoot.h>

typedef struct LOADED_MODULE
{
    const char* Name;
    void* Address;
    uint64_t Size;
    struct LOADED_MODULE* Next; /*List*/
} LOADED_MODULE;

#define LoaderCommand_LIST 1
#define LoaderCommand_GET 2
#define LoaderCommand_COUNT 3

extern LOADED_MODULE* LoadedModules;
extern SYSTEM_OPERATIONS LoaderOperations;
extern SYSTEM_NODE* LoaderNode;

LOADED_MODULE* Loader_GetModules(SYSTEM_ERROR*);
LOADED_MODULE* Loader_FindModule(const char*, SYSTEM_ERROR*);
uint64_t Loader_GetModuleCount(SYSTEM_ERROR*);
