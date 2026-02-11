#pragma once

#include <__KCONF.h>
#include <Errors.h>

extern uint8_t Pool[64 * 1024 * 1024];  /* 64 MB pool */
extern uint8_t* Pointer;
extern uint8_t* Ending;

void* StaticKMalloc(uint64_t, SYSTEM_ERROR*);
void StaticKFree(void*, SYSTEM_ERROR*);

void KickStartStaticPool(SYSTEM_ERROR*);