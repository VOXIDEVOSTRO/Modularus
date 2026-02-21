#pragma once

#include <__KCONF.h>
#include <Errors.h>
#include <VirtualFileSystem.h>

typedef struct SYSTEM_NODE SYSTEM_NODE;
typedef struct SYSTEM_FILE SYSTEM_FILE;

typedef struct SYSTEM_OPERATIONS
{
    int (*Open)(SYSTEM_NODE*, SYSTEM_FILE*, SYSTEM_ERROR*);
    int (*Close)(SYSTEM_FILE*, SYSTEM_ERROR*);
    long (*Read)(SYSTEM_FILE*, void*, uint64_t, SYSTEM_ERROR*);
    long (*Write)(SYSTEM_FILE*, const void*, uint64_t, SYSTEM_ERROR*);
    long (*Ioctl)(SYSTEM_FILE*, uint64_t, void*, SYSTEM_ERROR*);
    int (*Getattr)(SYSTEM_NODE*, VFS_STAT*, SYSTEM_ERROR*);
    int (*Setattr)(SYSTEM_NODE*, const VFS_STAT*, SYSTEM_ERROR*);
} SYSTEM_OPERATIONS;

typedef enum SYSTEM_NODE_TYPE_ENUMERATION
{
    SystemNodeTypeEnumeration_NONE,
    SystemNodeTypeEnumeration_FILE,
    SystemNodeTypeEnumeration_DIRECTORY,
    SystemNodeTypeEnumeration_SYMLINK,
} SYSTEM_NODE_TYPE_ENUMERATION;

struct SYSTEM_FILE
{
    SYSTEM_NODE* Node;
    uint64_t Offset;
    uint64_t Flags;
    uint64_t ReferenceCount;
    void* Private;
};

struct SYSTEM_NODE
{
    const char* Name;
    SYSTEM_NODE_TYPE_ENUMERATION Type;
    const SYSTEM_OPERATIONS* Operations;
    SYSTEM_NODE* Parent;
    SYSTEM_NODE* Child;
    SYSTEM_NODE* Next;
    void* Context;
    uint64_t ContextSize;
    uint64_t Mode;
    uint64_t UserID;
    uint64_t GroupID;
    uint64_t ReferenceCount;
};

typedef struct SYSTEM_FILESYSTEM_INSTANCE
{
    SUPER_BLOCK* SuperBlock;
    SYSTEM_NODE* Root;
    uint64_t NodeCount;
    uint64_t FileCount;
} SYSTEM_FILESYSTEM_INSTANCE;

extern SYSTEM_NODE* SystemRoot;
extern SYSTEM_FILESYSTEM_INSTANCE* SystemInstance;
extern SYSTEM_NODE* NodePool;
extern uint64_t NodeAllocatedCount;
extern SYSTEM_FILE* FilePool;
extern uint64_t FileAllocatedCount;
extern const uint64_t MaxSystemNodes;
extern const uint64_t MaxSystemFiles;

extern FILESYSTEM_TYPE SystemFileSystemType;
extern SUPER_OPERATIONS SystemSuperOperations;
extern VFS_NODE_OPERATIONS SystemBasicOperations;

int System_KickStart(SYSTEM_ERROR*);
int System_PowerOff(SYSTEM_ERROR*);

SYSTEM_NODE* System_CreateNode(const char*, SYSTEM_NODE_TYPE_ENUMERATION, const SYSTEM_OPERATIONS*, void*, uint64_t, SYSTEM_ERROR*);
int System_DeleteNode(SYSTEM_NODE*, SYSTEM_ERROR*);
SYSTEM_NODE* System_FindNode(SYSTEM_NODE*, const char*, SYSTEM_ERROR*);
SYSTEM_NODE* System_GetRoot(SYSTEM_ERROR*);
int System_AttachNode(SYSTEM_NODE*, SYSTEM_NODE*, SYSTEM_ERROR*);
int System_DetachNode(SYSTEM_NODE*, SYSTEM_ERROR*);

SYSTEM_NODE* System_CreateFile(const char*, const SYSTEM_OPERATIONS*, void*, uint64_t, SYSTEM_ERROR*);
SYSTEM_NODE* System_CreateDirectory(const char*, SYSTEM_ERROR*);

int System_Open(VFS_NODE*, FILE*, SYSTEM_ERROR*);
int System_Close(FILE*, SYSTEM_ERROR*);
long System_Read(FILE*, void*, long, SYSTEM_ERROR*);
long System_Write(FILE*, const void*, long, SYSTEM_ERROR*);
int System_Ioctl(FILE*, uint64_t, void*, SYSTEM_ERROR*);

long System_ReadDirectory(VFS_NODE*, void*, long, SYSTEM_ERROR*);
VFS_NODE* System_LookUp(VFS_NODE*, const char*, SYSTEM_ERROR*);

int System_Stat(VFS_NODE*, VFS_STAT*, SYSTEM_ERROR*);
int System_GetAttribute(SYSTEM_NODE*, VFS_STAT*, SYSTEM_ERROR*);
int System_SetAttribute(SYSTEM_NODE*, const VFS_STAT*, SYSTEM_ERROR*);

int System_StatFileSystem(SUPER_BLOCK*, VFS_STAT_FILESYSTEM*, SYSTEM_ERROR*);
int System_Sync(SUPER_BLOCK*, SYSTEM_ERROR*);
void System_Release(SUPER_BLOCK*, SYSTEM_ERROR*);

int System_SetContext(SYSTEM_NODE*, void*, uint64_t, SYSTEM_ERROR*);
void* System_GetContext(SYSTEM_NODE*, SYSTEM_ERROR*);
uint64_t System_GetContextSize(SYSTEM_NODE*, SYSTEM_ERROR*);

SYSTEM_NODE* System_Walk(const char*, SYSTEM_ERROR*);

int System_RegisterFileSystem(SYSTEM_ERROR*);
int System_UnRegisterFileSystem(SYSTEM_ERROR*);

SUPER_BLOCK* System_Mount(const char*, const char*, SYSTEM_ERROR*);
int System_UnMount(SUPER_BLOCK*, SYSTEM_ERROR*);

KEXPORT(System_KickStart)
KEXPORT(System_PowerOff)

KEXPORT(System_CreateNode)
KEXPORT(System_DeleteNode)
KEXPORT(System_FindNode)
KEXPORT(System_GetRoot)
KEXPORT(System_AttachNode)
KEXPORT(System_DetachNode)

KEXPORT(System_CreateFile)
KEXPORT(System_CreateDirectory)

KEXPORT(System_Open)
KEXPORT(System_Close)
KEXPORT(System_Read)
KEXPORT(System_Write)
KEXPORT(System_Ioctl)

KEXPORT(System_ReadDirectory)
KEXPORT(System_LookUp)

KEXPORT(System_Stat)
KEXPORT(System_GetAttribute)
KEXPORT(System_SetAttribute)

KEXPORT(System_StatFileSystem)
KEXPORT(System_Sync)
KEXPORT(System_Release)

KEXPORT(System_SetContext)
KEXPORT(System_GetContext)
KEXPORT(System_GetContextSize)

KEXPORT(System_Walk)

KEXPORT(System_RegisterFileSystem)
KEXPORT(System_UnRegisterFileSystem)

KEXPORT(System_Mount)
KEXPORT(System_UnMount)