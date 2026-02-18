#pragma once

/*totally the entire VFS is not stolen from https://github.com/VOXIDEVOSTRO/AxeialOS*/

#include <Types.h>
#include <Errors.h>
#include <KExports.h>

typedef struct VFS_NODE             VFS_NODE;
typedef struct DIRECTORY_ENTRY      DIRECTORY_ENTRY;
typedef struct SUPER_BLOCK          SUPER_BLOCK;
typedef struct FILE                 FILE;
typedef struct FILESYSTEM_TYPE      FILESYSTEM_TYPE;
typedef struct VFS_NODE_OPERATIONS  VFS_NODE_OPERATIONS;
typedef struct SUPER_OPERATIONS     SUPER_OPERATIONS;
typedef struct VFS_DIRECTORY_ENTRY  VFS_DIRECTORY_ENTRY;
typedef struct VFS_STAT             VFS_STAT;
typedef struct VFS_STAT_FILESYSTEM  VFS_STAT_FILESYSTEM;
typedef struct VFS_PERMISSIONS      VFS_PERMISSIONS;
typedef struct VFS_TIME             VFS_TIME;
typedef struct VFS_MOUNT_FLAGS      VFS_MOUNT_FLAGS;
typedef struct VFS_NAME_BUFFER      VFS_NAME_BUFFER;

/*Node Type*/
typedef enum VFS_NODE_TYPE
{
    VFSNode_NONE,
    VFSNode_FILE,
    VFSNode_DIRECTORY,
    VFSNode_DEVICE,
    VFSNode_SYMBOL,
    VFSNode_FIFO,
    VFSNode_SOCKET
} VFS_NODE_TYPE;

/*Open Flags*/
typedef enum VFS_OPEN_FLAGS
{
    VFS_OpenFlag_NONE      = 0,
    VFS_OpenFlag_READONLY = 1 << 0,
    VFS_OpenFlag_WRITEONLY= 1 << 1,
    VFS_OpenFlag_READWRITE= 1 << 2,
    VFS_OpenFlag_CREATE   = 1 << 3,
    VFS_OpenFlag_TRUNCATE = 1 << 4,
    VFS_OpenFlag_APPEND   = 1 << 5,
    VFS_OpenFlag_EXCLUDE  = 1 << 6,
    VFS_OpenFlag_SYNC     = 1 << 7,
    VFS_OpenFlag_DIRECT   = 1 << 8
} VFS_OPEN_FLAGS;

/*Seek Wheel*/
typedef enum VFS_SEEK_WHENCE
{
    VFSSeek_SET,
    VFSSeek_CURRENT,
    VFSSeek_END
} VFS_SEEK_WHENCE;

/*Permissions*/
typedef enum VFS_PERMISSION_MODE
{
    VFSMode_NONE = 0,

    /* User */
    VFSMode_RUSR = 1 << 8,
    VFSMode_WUSR = 1 << 7,
    VFSMode_XUSR = 1 << 6,

    /* Group */
    VFSMode_RGRP = 1 << 5,
    VFSMode_WGRP = 1 << 4,
    VFSMode_XGRP = 1 << 3,

    /* Other */
    VFSMode_ROTH = 1 << 2,
    VFSMode_WOTH = 1 << 1,
    VFSMode_XOTH = 1 << 0
} VFS_PERMISSION_MODE;

/*IO*/
typedef enum VFS_IO_FLAGS
{
    VFSIO_NONE    = 0,
    VFSIO_FUA     = 1 << 0,
    VFSIO_SYNC    = 1 << 1,
    VFSIO_NOCACHE = 1 << 2
} VFS_IO_FLAGS;

/*Mount*/
typedef enum VFS_MOUNT_OPTION
{
    VFS_Mount_NONE      = 0,
    VFS_Mount_READONLY  = 1 << 0,
    VFS_Mount_NOEXECUTE = 1 << 1,
    VFS_Mount_NODEVICE  = 1 << 2,
    VFS_Mount_NOSUID    = 1 << 3,
    VFS_Mount_SYNC      = 1 << 4,
    VFS_Mount_NOATIME   = 1 << 5
} VFS_MOUNT_OPTION;

/*Name*/
typedef enum VFS_RENAME_FLAGS
{
    VFS_ReName_NONE      = 0,
    VFS_ReName_NOREPLACE = 1 << 0,
    VFS_ReName_EXCHANGE  = 1 << 1,
    VFS_ReName_WHITEOUT  = 1 << 2
} VFS_RENAME_FLAGS;

/*Notify*/
typedef enum VFS_NOTIFY_MASK
{
    VFSNotify_NONE      = 0,
    VFSNotify_CREATE    = 1 << 0,
    VFSNotify_DELETE    = 1 << 1,
    VFSNotify_WRITE     = 1 << 2,
    VFSNotify_MOVE      = 1 << 3,
    VFSNotify_ATTRIBUTE = 1 << 4
} VFS_NOTIFY_MASK;

typedef struct VFS_TIME
{
    long Second;
    long NanoSecond;
} VFS_TIME;

typedef struct VFS_PERMISSIONS
{
    /*Mains*/
    long Mode;

    /*Ids*/
    long UserID;
    long GroupID;
} VFS_PERMISSIONS;

typedef struct VFS_STAT
{
    /*Mains*/
    long Inode;
    long Size;
    long Blocks;
    long BlockSize;
    long NumberOfLinks;
    long RawDevice;
    long Device;
    long Flags;

    /*Attr*/
    VFS_NODE_TYPE   Type;
    VFS_PERMISSIONS Permission;

    /*Time*/
    VFS_TIME Atime;
    VFS_TIME Mtime;
    VFS_TIME Ctime;
} VFS_STAT;

typedef struct VFS_STAT_FILESYSTEM
{
    long TypeID;
    long BlockSize;
    long Blocks;
    long BlocksFree;
    long BlocksAvailable;
    long Files;
    long FilesFree;
    long NameLength;
    long Flags;
} VFS_STAT_FILESYSTEM;

typedef struct VFS_DIRECTORY_ENTRY
{
    char Name[256];
    long Type;
    long Inode;
} VFS_DIRECTORY_ENTRY; /*Dirent*/

typedef struct VFS_NAME_BUFFER
{
    char* Buffer;
    long  Length;
} VFS_NAME_BUFFER;

typedef struct VFS_NODE_OPERATIONS
{
    int (*Open)(VFS_NODE*, FILE*, SYSTEM_ERROR*);
    int (*Close)(FILE*, SYSTEM_ERROR*);
    long (*Read)(FILE*, void*, long, SYSTEM_ERROR*);
    long (*Write)(FILE*, const void*, long, SYSTEM_ERROR*);
    long (*Lseek)(FILE*, long, int, SYSTEM_ERROR*);
    int (*Ioctl)(FILE*, uint64_t, void*, SYSTEM_ERROR*);
    int (*Stat)(VFS_NODE*, VFS_STAT*, SYSTEM_ERROR*);
    long (*Readdir)(VFS_NODE*, void*, long, SYSTEM_ERROR*);
    VFS_NODE* (*Lookup)(VFS_NODE*, const char*, SYSTEM_ERROR*);
    int (*Create)(VFS_NODE*, const char*, long, VFS_PERMISSIONS, SYSTEM_ERROR*);
    int (*Unlink)(VFS_NODE*, const char*, SYSTEM_ERROR*);
    int (*Mkdir)(VFS_NODE*, const char*, VFS_PERMISSIONS, SYSTEM_ERROR*);
    int (*Rmdir)(VFS_NODE*, const char*, SYSTEM_ERROR*);
    int (*Symlink)(VFS_NODE*, const char*, const char*, VFS_PERMISSIONS, SYSTEM_ERROR*);
    int (*Readlink)(VFS_NODE*, VFS_NAME_BUFFER*, SYSTEM_ERROR*);
    int (*Link)(VFS_NODE*, VFS_NODE*, const char*, SYSTEM_ERROR*);
    int (*Rename)(VFS_NODE*, const char*, VFS_NODE*, const char*, long, SYSTEM_ERROR*);
    int (*Chmod)(VFS_NODE*, long, SYSTEM_ERROR*);
    int (*Chown)(VFS_NODE*, long, long, SYSTEM_ERROR*);
    int (*Truncate)(VFS_NODE*, long, SYSTEM_ERROR*);
    int (*Sync)(VFS_NODE*, SYSTEM_ERROR*);
    int (*Map)(VFS_NODE*, void**, long, long, SYSTEM_ERROR*);
    int (*Unmap)(VFS_NODE*, void*, long, SYSTEM_ERROR*);
} VFS_NODE_OPERATIONS;

typedef struct SUPER_OPERATIONS
{
    int (*Sync)(SUPER_BLOCK*, SYSTEM_ERROR*);
    int (*StatFs)(SUPER_BLOCK*, VFS_STAT_FILESYSTEM*, SYSTEM_ERROR*);
    void (*Release)(SUPER_BLOCK*, SYSTEM_ERROR*);
    int (*Umount)(SUPER_BLOCK*, SYSTEM_ERROR*);
} SUPER_OPERATIONS;

typedef struct FILESYSTEM_TYPE
{
    const char* Name;
    SUPER_BLOCK* (*Mount)(const char*, const char*, SYSTEM_ERROR*);
    void* Private;
} FILESYSTEM_TYPE;

/*SUPER_BLOCK*/
struct SUPER_BLOCK
{
    const FILESYSTEM_TYPE* Type;
    void* Device;
    long Flags;
    VFS_NODE* Root;
    const SUPER_OPERATIONS* Operations;
    void* Private;
};

/*Nodes*/
struct VFS_NODE
{
    VFS_NODE_TYPE Type;
    const VFS_NODE_OPERATIONS* Operations;
    SUPER_BLOCK* SuperBlock;
    void* Private;
    long ReferenceCount;
};

struct DIRECTORY_ENTRY
{
    const char* Name;
    DIRECTORY_ENTRY* Parent;
    VFS_NODE* Node;
    long Flags;
};

struct FILE
{
    VFS_NODE* Node;
    long Offset;
    long Flags;
    long ReferenceCount;
    void* Private;
};


extern const long MaxFileSystemTypes;
extern const long MaxMounts;
extern const FILESYSTEM_TYPE* FileSystemRegistry[32];
extern long FileSystemCount;

typedef struct MOUNT_ENTRY
{
    SUPER_BLOCK* SuperBlock;
    char Path[1024];
} MOUNT_ENTRY;

extern MOUNT_ENTRY Mounts[64];
extern long MountsCount;
extern VFS_NODE* RootNode;
extern DIRECTORY_ENTRY* RootDirectoryEntry;
extern long  UnMask;
extern long  MaxName;
extern long  MaxPath;
extern long  DirectoryCacheLimit;
extern long  FileCacheLimit;
extern long  IOBlockSize;
extern char  DefaultFileSystem[64];

int VFS_KickStart(SYSTEM_ERROR*);
int VFS_PowerOff(SYSTEM_ERROR*);

int VFS_RegisterFileSystem(const FILESYSTEM_TYPE*, SYSTEM_ERROR*);
int VFS_UnRegisterFileSystem(const char*, SYSTEM_ERROR*);
const FILESYSTEM_TYPE* VFS_FindFileSystem(const char*, SYSTEM_ERROR*);
long VfsListFs(const char**, long, SYSTEM_ERROR*);

SUPER_BLOCK* VFS_Mount(const char*, const char*, const char*, long, const char*, SYSTEM_ERROR*);
int VFS_UnMount(const char*, SYSTEM_ERROR*);
int VFS_ChangeRoot(const char*, SYSTEM_ERROR*);

int VFS_BindMount(const char*, const char*, SYSTEM_ERROR*);
int VFS_MoveMount(const char*, const char*, SYSTEM_ERROR*);
int VFS_ReMount(const char*, long, const char*, SYSTEM_ERROR*);

DIRECTORY_ENTRY* VFS_Resolve(const char*, SYSTEM_ERROR*);
DIRECTORY_ENTRY* VFS_ResolveAt(DIRECTORY_ENTRY*, const char*, SYSTEM_ERROR*);
VFS_NODE* VFS_LookUp(DIRECTORY_ENTRY*, const char*, SYSTEM_ERROR*);
int VFS_MakePath(const char*, long, SYSTEM_ERROR*);
int VFS_RealPath(const char*, char*, long, SYSTEM_ERROR*);

FILE* VFS_Open(const char*, long, SYSTEM_ERROR*);
FILE* VFS_OpenAt(DIRECTORY_ENTRY*, const char*, long, SYSTEM_ERROR*);
int VFS_Close(FILE*, SYSTEM_ERROR*);
long VFS_Read(FILE*, void*, long, SYSTEM_ERROR*);
long VFS_Write(FILE*, const void*, long, SYSTEM_ERROR*);
long VFS_LSeek(FILE*, long, int, SYSTEM_ERROR*);
int VFS_IOControl(FILE*, uint64_t, void*, SYSTEM_ERROR*);
int VFS_FSync(FILE*, SYSTEM_ERROR*);
int VFS_FStats(FILE*, VFS_STAT*, SYSTEM_ERROR*);
int VFS_Stats(const char*, VFS_STAT*, SYSTEM_ERROR*);

long VFS_ReadDirectory(const char*, void*, long, SYSTEM_ERROR*);
long VFS_ReadDirectoryF(FILE*, void*, long, SYSTEM_ERROR*);

int VFS_Create(const char*, long, VFS_PERMISSIONS, SYSTEM_ERROR*);
int VFS_UnLink(const char*, SYSTEM_ERROR*);
int VFS_MakeDirectory(const char*, VFS_PERMISSIONS, SYSTEM_ERROR*);
int VFS_RemoveDirectory(const char*, SYSTEM_ERROR*);
int VFS_SymbolLink(const char*, const char*, VFS_PERMISSIONS, SYSTEM_ERROR*);
int VFS_ReadLink(const char*, char*, long, SYSTEM_ERROR*);
int VFS_Link(const char*, const char*, SYSTEM_ERROR*);
int VFS_ReName(const char*, const char*, long, SYSTEM_ERROR*);
int VFS_ChangeMode(const char*, long, SYSTEM_ERROR*);
int VFS_ChangeOwner(const char*, long, long, SYSTEM_ERROR*);
int VFS_Truncate(const char*, long, SYSTEM_ERROR*);

int VFS_NodeReferenceIncrement(VFS_NODE*, SYSTEM_ERROR*);
int VFS_NodeReferenceDecrement(VFS_NODE*, SYSTEM_ERROR*);
int VFS_NodeGetAttribute(VFS_NODE*, VFS_STAT*, SYSTEM_ERROR*);
int VFS_NodeSetAttribute(VFS_NODE*, const VFS_STAT*, SYSTEM_ERROR*);
int VFS_DentryInvalidate(DIRECTORY_ENTRY*, SYSTEM_ERROR*);
int VFS_DentryRevalidate(DIRECTORY_ENTRY*, SYSTEM_ERROR*);
int VFS_DentryAttach(DIRECTORY_ENTRY*, VFS_NODE*, SYSTEM_ERROR*);
int VFS_DentryDetach(DIRECTORY_ENTRY*, SYSTEM_ERROR*);
int VFS_DentryName(DIRECTORY_ENTRY*, char*, long, SYSTEM_ERROR*);

int VFS_SetWorkingDirectory(const char*, SYSTEM_ERROR*);
int VFS_GetWorkingDirectory(char*, long, SYSTEM_ERROR*);
int VFS_SetRoot(const char*, SYSTEM_ERROR*);
int VFS_GetRoot(char*, long, SYSTEM_ERROR*);

int  VFS_SetUnMask(long, SYSTEM_ERROR*);
long VFS_GetUnMask(SYSTEM_ERROR*);

int VFS_NotifySubscribe(const char*, long, SYSTEM_ERROR*);
int VFS_NotifyUnSubscribe(const char*, SYSTEM_ERROR*);
int VFS_NotifyPoll(const char*, long*, SYSTEM_ERROR*);

int VFS_Access(const char*, long, SYSTEM_ERROR*);
int VFS_Exists(const char*, SYSTEM_ERROR*);
int VFS_IsDirectory(const char*, SYSTEM_ERROR*);
int VFS_IsFile(const char*, SYSTEM_ERROR*);
int VFS_IsSymbolLink(const char*, SYSTEM_ERROR*);

int VFS_Copy(const char*, const char*, long, SYSTEM_ERROR*);
int VFS_Move(const char*, const char*, long, SYSTEM_ERROR*);

int VFS_ReadAll(const char*, void*, long, long*, SYSTEM_ERROR*);
int VFS_WriteAll(const char*, const void*, long, SYSTEM_ERROR*);

int VFS_MountTableEnumerate(char*, long, SYSTEM_ERROR*);
int VFS_MountTableFind(const char*, char*, long, SYSTEM_ERROR*);

int VFS_NodePath(VFS_NODE*, char*, long, SYSTEM_ERROR*);
int VFS_NodeName(VFS_NODE*, char*, long, SYSTEM_ERROR*);

int VFS_AllocateName(char**, long, SYSTEM_ERROR*);
int VFS_FreeName(char*, SYSTEM_ERROR*);
int VFS_JoinPath(const char*, const char*, char*, long, SYSTEM_ERROR*);

int  VFS_SetFlag(const char*, long, SYSTEM_ERROR*);
int  VFS_ClearFlag(const char*, long, SYSTEM_ERROR*);
long VFS_GetFlags(const char*, SYSTEM_ERROR*);

int VFS_SyncAll(SYSTEM_ERROR*);
int VFS_PruneCaches(SYSTEM_ERROR*);

int VFS_RegisterDeviceNode(const char*, void*, long, SYSTEM_ERROR*);
int VFS_UnRegisterDeviceNode(const char*, SYSTEM_ERROR*);
int VFS_RegisterPseudoFileSystem(const char*, SUPER_BLOCK*, SYSTEM_ERROR*);
int VFS_UnRegisterPseudoFileSystem(const char*, SYSTEM_ERROR*);

int VFS_SetDefaultFileSystem(const char*, SYSTEM_ERROR*);
const char* VFS_GetDefaultFileSystem(SYSTEM_ERROR*);

int  VFS_SetMaxName(long, SYSTEM_ERROR*);
long VFS_GetMaxName(SYSTEM_ERROR*);

int  VFS_SetMaxPath(long, SYSTEM_ERROR*);
long VFS_GetMaxPath(SYSTEM_ERROR*);

int  VFS_SetDirectoryCacheLimit(long, SYSTEM_ERROR*);
long VFS_GetDirectoryCacheLimit(SYSTEM_ERROR*);

int  VFS_SetFileCacheLimit(long, SYSTEM_ERROR*);
long VFS_GetFileCacheLimit(SYSTEM_ERROR*);

int  VFS_SetIOBlockSize(long, SYSTEM_ERROR*);
long VFS_GetIOBlockSize(SYSTEM_ERROR*);

/*VFS_StringHelpers.c*/
int IsSeperator(char, SYSTEM_ERROR*);
const char* SkipSeperator(const char*, SYSTEM_ERROR*);
long NextCompare(const char* Path, char* Output, long Capacity, SYSTEM_ERROR* Error);

/*VFS_CoreHelpers.c*/
DIRECTORY_ENTRY* AllocateDirectoryEntry(const char*, DIRECTORY_ENTRY*, VFS_NODE*, SYSTEM_ERROR*);
DIRECTORY_ENTRY* Walk(VFS_NODE*, DIRECTORY_ENTRY*, const char*, SYSTEM_ERROR*);
MOUNT_ENTRY* FindMount(const char*, SYSTEM_ERROR*);

/*
    APIS!
*/

KEXPORT(VFS_KickStart)
KEXPORT(VFS_PowerOff)
KEXPORT(VFS_RegisterFileSystem)
KEXPORT(VFS_UnRegisterFileSystem)
KEXPORT(VFS_FindFileSystem)
KEXPORT(VfsListFs)
KEXPORT(VFS_Mount)
KEXPORT(VFS_UnMount)
KEXPORT(VFS_ChangeRoot)
KEXPORT(VFS_BindMount)
KEXPORT(VFS_MoveMount)
KEXPORT(VFS_ReMount)
KEXPORT(VFS_Resolve)
KEXPORT(VFS_ResolveAt)
KEXPORT(VFS_LookUp)
KEXPORT(VFS_MakePath)
KEXPORT(VFS_RealPath)
KEXPORT(VFS_Open)
KEXPORT(VFS_OpenAt)
KEXPORT(VFS_Close)
KEXPORT(VFS_Read)
KEXPORT(VFS_Write)
KEXPORT(VFS_LSeek)
KEXPORT(VFS_IOControl)
KEXPORT(VFS_FSync)
KEXPORT(VFS_FStats)
KEXPORT(VFS_Stats)
KEXPORT(VFS_ReadDirectory)
KEXPORT(VFS_ReadDirectoryF)
KEXPORT(VFS_Create)
KEXPORT(VFS_UnLink)
KEXPORT(VFS_MakeDirectory)
KEXPORT(VFS_RemoveDirectory)
KEXPORT(VFS_SymbolLink)
KEXPORT(VFS_ReadLink)
KEXPORT(VFS_Link)
KEXPORT(VFS_ReName)
KEXPORT(VFS_ChangeMode)
KEXPORT(VFS_ChangeOwner)
KEXPORT(VFS_Truncate)
KEXPORT(VFS_NodeReferenceIncrement)
KEXPORT(VFS_NodeReferenceDecrement)
KEXPORT(VFS_NodeGetAttribute)
KEXPORT(VFS_NodeSetAttribute)
KEXPORT(VFS_DentryInvalidate)
KEXPORT(VFS_DentryRevalidate)
KEXPORT(VFS_DentryAttach)
KEXPORT(VFS_DentryDetach)
KEXPORT(VFS_DentryName)
KEXPORT(VFS_SetWorkingDirectory)
KEXPORT(VFS_GetWorkingDirectory)
KEXPORT(VFS_SetRoot)
KEXPORT(VFS_GetRoot)
KEXPORT(VFS_SetUnMask)
KEXPORT(VFS_GetUnMask)
KEXPORT(VFS_NotifySubscribe)
KEXPORT(VFS_NotifyUnSubscribe)
KEXPORT(VFS_NotifyPoll)
KEXPORT(VFS_Access)
KEXPORT(VFS_Exists)
KEXPORT(VFS_IsDirectory)
KEXPORT(VFS_IsFile)
KEXPORT(VFS_IsSymbolLink)
KEXPORT(VFS_Copy)
KEXPORT(VFS_Move)
KEXPORT(VFS_ReadAll)
KEXPORT(VFS_WriteAll)
KEXPORT(VFS_JoinPath)
KEXPORT(VFS_SetFlag)
KEXPORT(VFS_ClearFlag)
KEXPORT(VFS_GetFlags)
KEXPORT(VFS_SyncAll)
KEXPORT(VFS_PruneCaches)
KEXPORT(VFS_SetDefaultFileSystem)
KEXPORT(VFS_GetDefaultFileSystem)
KEXPORT(VFS_SetMaxName)
KEXPORT(VFS_GetMaxName)
KEXPORT(VFS_SetMaxPath)
KEXPORT(VFS_GetMaxPath)
KEXPORT(VFS_SetDirectoryCacheLimit)
KEXPORT(VFS_GetDirectoryCacheLimit)
KEXPORT(VFS_SetFileCacheLimit)
KEXPORT(VFS_GetFileCacheLimit)
KEXPORT(VFS_SetIOBlockSize)
KEXPORT(VFS_GetIOBlockSize)