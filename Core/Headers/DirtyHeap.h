#pragma once

#include <__KCONF.h>
#include <Errors.h>
#include <KExports.h>

#include <CTools.h>
#include <Types.h>

typedef struct DIRTY_HEAP_OPERATIONS
{
    void* (*Alloc)(uint64_t, SYSTEM_ERROR*);
    void (*Free)(void*, SYSTEM_ERROR*);
} DIRTY_HEAP_OPERATIONS;

typedef struct DIRTY_HEAP
{
    const char* Name;
    DIRTY_HEAP_OPERATIONS* Operations; 
} DIRTY_HEAP;

extern DIRTY_HEAP* DirtyHeap;

void* KMalloc(uint64_t, SYSTEM_ERROR*);
void KFree(void*, SYSTEM_ERROR*);

KEXPORT(KMalloc);
KEXPORT(KFree);

KEXPORT(DirtyHeap);