#pragma once

#include <__KCONF.h>
#include <Errors.h>

extern uint8_t Pool[64 * 1024 * 1024];  /* 64 MB pool */
extern uint8_t* Pointer;
extern uint8_t* Ending;

void* KMalloc(uint64_t, SYSTEM_ERROR*);
void KFree(void*, SYSTEM_ERROR*);

