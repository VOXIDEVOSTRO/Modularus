#pragma once

/*
    IS TODO, partially made the header
*/

#include <__KCONF.h>
#include <Errors.h>
#include <VirtualFileSystem.h>

typedef struct SYSTEM_OPERATIONS
{
    int (*Open)(void*, SYSTEM_ERROR*);
    int (*Close)(void*, SYSTEM_ERROR*);
    long (*Read)(void*, void*, long, SYSTEM_ERROR*);
    long (*Write)(void*, const void*, long, SYSTEM_ERROR*);
    int (*Ioctl)(void*, unsigned long, void*, SYSTEM_ERROR*);
} SYSTEM_OPERATIONS;

typedef struct SYSTEM_NODE
{
    const char* Name;
    SYSTEM_OPERATIONS* Operations;

    /*Tree*/
    struct SYSTEM_NODE* Parent;
    struct SYSTEM_NODE* Child;
    struct SYSTEM_NODE* Next;

    void* Context;
} SYSTEM_NODE;

extern SYSTEM_NODE* SystemRoot;