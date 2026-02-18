#pragma once

/*Error codes with trace backs*/

/*Global*/
typedef
enum
{
    GeneralOK,

    EPERM           = 1,   /* Operation not permitted */                /* 1 */ 
    ENOENT          = 2,   /* No such file or directory */             /* 2 */
    ESRCH           = 3,   /* No such process */                        /* 3 */
    EINTR           = 4,   /* Interrupted system call */               /* 4 */
    EIO             = 5,   /* I/O error */                              /* 5 */
    ENXIO           = 6,   /* No such device or address */             /* 6 */
    E2BIG           = 7,   /* Argument list too long */                /* 7 */
    ENOEXEC         = 8,   /* Exec format error */                     /* 8 */
    EBADF           = 9,   /* Bad file descriptor */                   /* 9 */
    ECHILD          = 10,  /* No child processes */                    /* 10 */
    EAGAIN          = 11,  /* Resource temporarily unavailable */      /* 11 */
    EWOULDBLOCK     = 11,  /* Same as EAGAIN: would block */           /* 11 */
    ENOMEM          = 12,  /* Cannot allocate memory */                /* 12 */
    EACCES          = 13,  /* Permission denied */                     /* 13 */
    EFAULT          = 14,  /* Bad address */                            /* 14 */
    ENOTBLK         = 15,  /* Block device required */                 /* 15 */
    EBUSY           = 16,  /* Device or resource busy */               /* 16 */
    EEXIST          = 17,  /* File exists */                            /* 17 */
    EXDEV           = 18,  /* Invalid cross-device link */             /* 18 */
    ENODEV          = 19,  /* No such device */                        /* 19 */
    ENOTDIR         = 20,  /* Not a directory */                       /* 20 */
    EISDIR          = 21,  /* Is a directory */                        /* 21 */
    EINVAL          = 22,  /* Invalid argument */                      /* 22 */
    ENFILE          = 23,  /* File table overflow */                   /* 23 */
    EMFILE          = 24,  /* Too many open files */                   /* 24 */
    ENOTTY          = 25,  /* Inappropriate ioctl for device */        /* 25 */
    ETXTBSY         = 26,  /* Text file busy */                         /* 26 */
    EFBIG           = 27,  /* File too large */                         /* 27 */
    ENOSPC          = 28,  /* No space left on device */               /* 28 */
    ESPIPE          = 29,  /* Illegal seek */                           /* 29 */
    EROFS           = 30,  /* Read‑only file system */                 /* 30 */
    EMLINK          = 31,  /* Too many links */                         /* 31 */
    EPIPE           = 32,  /* Broken pipe */                            /* 32 */
    EDOM            = 33,  /* Numerical argument out of domain */      /* 33 */
    ERANGE          = 34,  /* Numerical result out of range */         /* 34 */
    EDEADLK         = 35,  /* Resource deadlock avoided */             /* 35 */
    ENAMETOOLONG    = 36,  /* File name too long */                    /* 36 */
    ENOLCK          = 37,  /* No record locks available */             /* 37 */
    ENOSYS          = 38,  /* Function not implemented */              /* 38 */
    ENOTEMPTY       = 39,  /* Directory not empty */                    /* 39 */
    ELOOP           = 40,  /* Too many symbolic links encountered */   /* 40 */
    ENOMSG          = 42,  /* No message of desired type */            /* 42 */
    EIDRM           = 43,  /* Identifier removed */                    /* 43 */
    ECHRNG          = 44,  /* Channel number out of range */           /* 44 */
    EL2NSYNC        = 45,  /* Level 2 not synchronized */              /* 45 */
    EL3HLT          = 46,  /* Level 3 halted */                         /* 46 */
    EL3RST          = 47,  /* Level 3 reset */                          /* 47 */
    ELNRNG          = 48,  /* Link number out of range */              /* 48 */
    EUNATCH         = 49,  /* Protocol driver not attached */          /* 49 */
    ENOCSI          = 50,  /* No CSI structure available */            /* 50 */
    EL2HLT          = 51,  /* Level 2 halted */                         /* 51 */
    EBADE           = 52,  /* Invalid exchange */                       /* 52 */
    EBADR           = 53,  /* Invalid request descriptor */           /* 53 */
    EXFULL          = 54,  /* Exchange full */                         /* 54 */
    ENOANO          = 55,  /* No anode */                               /* 55 */
    EBADRQC         = 56,  /* Invalid request code */                  /* 56 */
    EBADSLT         = 57,  /* Invalid slot */                           /* 57 */
    EBFONT          = 59,  /* Bad font file format */                  /* 59 */
    ENOSTR          = 60,  /* Device not a stream */                   /* 60 */
    ENODATA         = 61,  /* No data available */                     /* 61 */
    ETIME           = 62,  /* Timer expired */                          /* 62 */
    ENOSR           = 63,  /* Out of streams resources */              /* 63 */
    ENONET          = 64,  /* Machine is not on the network */         /* 64 */
    ENOPKG          = 65,  /* Package not installed */                /* 65 */
    EREMOTE         = 66,  /* Object is remote */                      /* 66 */
    ENOLINK         = 67,  /* Link has been severed */                 /* 67 */
    EADV            = 68,  /* Advertise error */                       /* 68 */
    ESRMNT          = 69,  /* Srmount error */                         /* 69 */
    ECOMM           = 70,  /* Communication error on send */           /* 70 */
    EPROTO          = 71,  /* Protocol error */                        /* 71 */
    EMULTIHOP       = 72,  /* Multihop attempted */                    /* 72 */
    EDOTDOT         = 73,  /* RFS specific error */                    /* 73 */
    EBADMSG         = 74,  /* Not a data message */                    /* 74 */
    EOVERFLOW       = 75,  /* Value too large for defined data type */ /* 75 */
    ENOTUNIQ        = 76,  /* Name not unique on network */           /* 76 */
    EBADFD          = 77,  /* File descriptor in bad state */         /* 77 */
    EREMCHG         = 78,  /* Remote address changed */                /* 78 */
    ELIBACC         = 79,  /* Cannot access needed shared library */  /* 79 */
    ELIBBAD         = 80,  /* Corrupted shared library */              /* 80 */
    ELIBSCN         = 81,  /* .lib section in a.out corrupted */       /* 81 */
    ELIBMAX         = 82,  /* Too many shared libraries */             /* 82 */
    ELIBEXEC        = 83,  /* Cannot exec a shared library */         /* 83 */
    EILSEQ          = 84,  /* Illegal byte sequence */                /* 84 */
    ERESTART        = 85,  /* Interrupted system call should restart */ /* 85 */
    ESTRPIPE        = 86,  /* Streams pipe error */                   /* 86 */
    EOPNOTSUPP      = 95,  /* Operation not supported on endpoint */  /* 95 */
    EPFNOSUPPORT    = 96,  /* Protocol family not supported */        /* 96 */
    EAFNOSUPPORT    = 97,  /* Address family not supported */         /* 97 */
    EADDRINUSE      = 98,  /* Address already in use */              /* 98 */
    EADDRNOTAVAIL   = 99,  /* Cannot assign requested address */      /* 99 */
    ENETDOWN        = 100, /* Network is down */                      /* 100 */
    ENETUNREACH     = 101, /* Network unreachable */                /* 101 */
    ENETRESET       = 102, /* Network dropped connection on reset */ /* 102 */
    ECONNABORTED    = 103, /* Connection aborted */                 /* 103 */
    ECONNRESET      = 104, /* Connection reset by peer */           /* 104 */
    ENOBUFS         = 105, /* No buffer space available */          /* 105 */
    EISCONN         = 106, /* Already connected */                  /* 106 */
    ENOTCONN        = 107, /* Not connected */                      /* 107 */
    ESHUTDOWN       = 108, /* Cannot send after shutdown */         /* 108 */
    ETOOMANYREFS    = 109, /* Too many references */                /* 109 */
    ETIMEDOUT       = 110, /* Connection timed out */              /* 110 */
    ECONNREFUSED    = 111, /* Connection refused */               /* 111 */
    EHOSTDOWN       = 112, /* Host is down */                      /* 112 */
    EHOSTUNREACH    = 113, /* Host unreachable */                 /* 113 */
    EALREADY        = 114, /* Operation already in progress */     /* 114 */
    EINPROGRESS     = 115, /* Operation now in progress */        /* 115 */

    GeneralError,

    MaxErrors,
} ERROR_CODES;

/*Local*/
typedef
enum
{
    General,

    /*Main stuff*/
    FUNC_Limine_REQUEST,
    
    FUNC_LookUpKExport,

    FUNC_RegisterErrorKeys,

    /*VFS*/
    FUNC_VFS_KickStart,
    FUNC_VFS_PowerOff,
    FUNC_VFS_RegisterFileSystem,
    FUNC_VFS_UnRegisterFileSystem,
    FUNC_VFS_FindFileSystem,
    FUNC_VfsListFs,
    FUNC_VFS_Mount,
    FUNC_VFS_UnMount,
    FUNC_VFS_ChangeRoot,
    FUNC_VFS_BindMount,
    FUNC_VFS_MoveMount,
    FUNC_VFS_ReMount,
    FUNC_VFS_Resolve,
    FUNC_VFS_ResolveAt,
    FUNC_VFS_LookUp,
    FUNC_VFS_MakePath,
    FUNC_VFS_RealPath,
    FUNC_VFS_Open,
    FUNC_VFS_OpenAt,
    FUNC_VFS_Close,
    FUNC_VFS_Read,
    FUNC_VFS_Write,
    FUNC_VFS_LSeek,
    FUNC_VFS_IOControl,
    FUNC_VFS_FSync,
    FUNC_VFS_FStats,
    FUNC_VFS_Stats,
    FUNC_VFS_ReadDirectory,
    FUNC_VFS_ReadDirectoryF,
    FUNC_VFS_Create,
    FUNC_VFS_UnLink,
    FUNC_VFS_MakeDirectory,
    FUNC_VFS_RemoveDirectory,
    FUNC_VFS_SymbolLink,
    FUNC_VFS_ReadLink,
    FUNC_VFS_Link,
    FUNC_VFS_ReName,
    FUNC_VFS_ChangeMode,
    FUNC_VFS_ChangeOwner,
    FUNC_VFS_Truncate,
    FUNC_VFS_NodeReferenceIncrement,
    FUNC_VFS_NodeReferenceDecrement,
    FUNC_VFS_NodeGetAttribute,
    FUNC_VFS_NodeSetAttribute,
    FUNC_VFS_DentryInvalidate,
    FUNC_VFS_DentryRevalidate,
    FUNC_VFS_DentryAttach,
    FUNC_VFS_DentryDetach,
    FUNC_VFS_DentryName,
    FUNC_VFS_SetWorkingDirectory,
    FUNC_VFS_GetWorkingDirectory,
    FUNC_VFS_SetRoot,
    FUNC_VFS_GetRoot,
    FUNC_VFS_SetUnMask,
    FUNC_VFS_GetUnMask,
    FUNC_VFS_NotifySubscribe,
    FUNC_VFS_NotifyUnSubscribe,
    FUNC_VFS_NotifyPoll,
    FUNC_VFS_Access,
    FUNC_VFS_Exists,
    FUNC_VFS_IsDirectory,
    FUNC_VFS_IsFile,
    FUNC_VFS_IsSymbolLink,
    FUNC_VFS_Copy,
    FUNC_VFS_Move,
    FUNC_VFS_ReadAll,
    FUNC_VFS_WriteAll,
    FUNC_VFS_MountTableEnumerate,
    FUNC_VFS_MountTableFind,
    FUNC_VFS_NodePath,
    FUNC_VFS_NodeName,
    FUNC_VFS_AllocateName,
    FUNC_VFS_FreeName,
    FUNC_VFS_JoinPath,
    FUNC_VFS_SetFlag,
    FUNC_VFS_ClearFlag,
    FUNC_VFS_GetFlags,
    FUNC_VFS_SyncAll,
    FUNC_VFS_PruneCaches,
    FUNC_VFS_RegisterDeviceNode,
    FUNC_VFS_UnRegisterDeviceNode,
    FUNC_VFS_RegisterPseudoFileSystem,
    FUNC_VFS_UnRegisterPseudoFileSystem,
    FUNC_VFS_SetDefaultFileSystem,
    FUNC_VFS_GetDefaultFileSystem,
    FUNC_VFS_SetMaxName,
    FUNC_VFS_GetMaxName,
    FUNC_VFS_SetMaxPath,
    FUNC_VFS_GetMaxPath,
    FUNC_VFS_SetDirectoryCacheLimit,
    FUNC_VFS_GetDirectoryCacheLimit,
    FUNC_VFS_SetFileCacheLimit,
    FUNC_VFS_GetFileCacheLimit,
    FUNC_VFS_SetIOBlockSize,
    FUNC_VFS_GetIOBlockSize,
    FUNC_AllocateDirectoryEntry,
    FUNC_Walk,

    /*System*/
    FUNC_System_KickStart,
    FUNC_System_PowerOff,
    FUNC_System_CreateNode,
    FUNC_System_DeleteNode,
    FUNC_System_FindNode,
    FUNC_System_AttachNode,
    FUNC_System_DetachNode,
    FUNC_System_GetRoot,
    FUNC_System_CreateFile,
    FUNC_System_CreateDirectory,
    FUNC_System_Open,
    FUNC_System_Close,
    FUNC_System_Read,
    FUNC_System_Write,
    FUNC_System_ReadDirectory,
    FUNC_System_LookUp,
    FUNC_System_Stat,
    FUNC_System_GetAttribute,
    FUNC_System_SetAttribute,
    FUNC_System_StatFileSystem,
    FUNC_System_Sync,
    FUNC_System_Release,
    FUNC_System_SetContext,
    FUNC_System_GetContext,
    FUNC_System_GetContextSize,
    FUNC_System_Walk,
    FUNC_System_Mount,
    FUNC_System_UnMount,
    FUNC_System_RegisterFileSystem,
    FUNC_System_UnRegisterFileSystem,
    FUNC_System_Ioctl,

    MaxTraceback = 10000,
} TRACEBACK_ID; /*Can also be called function IDs*/

/*Core Error stuff*/
typedef
struct
{
    int ErrorCode;
    int TraceBack;
} SYSTEM_ERROR;

/*Main reporter*/
#define ErrorOut(ErrorSlot, Code, Trace)      \
    do                                        \
    {                                         \
        if ((ErrorSlot) != NULL)              \
        {                                     \
            (ErrorSlot)->ErrorCode = (Code);  \
            (ErrorSlot)->TraceBack = (Trace); \
        }                                     \
    } while (0)

/*For Pointers ofc*/
#define Error2Pointer(Code)((void*)(intptr_t)(Code))
#define Pointer2Error(Pointer)((int)(intptr_t)(Pointer))
#define Probe4Error(Pointer)((intptr_t)(Pointer) < 0 && (intptr_t)(Pointer) >= -MaxErrors)

/*String maps for the error code enum*/
/*Global*/
static const char*
ErrorMap[MaxErrors]=
{
    [0]  = "Success",
    [1]  = "Operation not permitted",
    [2]  = "No such file or directory",
    [3]  = "No such process",
    [4]  = "Interrupted system call",
    [5]  = "I/O error",
    [6]  = "No such device or address",
    [7]  = "Argument list too long",
    [8]  = "Exec format error",
    [9]  = "Bad file descriptor",
    [10] = "No child processes",
    [11] = "Resource temporarily unavailable / would block",
    [12] = "Cannot allocate memory",
    [13] = "Permission denied",
    [14] = "Bad address",
    [15] = "Block device required",
    [16] = "Device or resource busy",
    [17] = "File exists",
    [18] = "Invalid cross-device link",
    [19] = "No such device",
    [20] = "Not a directory",
    [21] = "Is a directory",
    [22] = "Invalid argument",
    [23] = "File table overflow",
    [24] = "Too many open files",
    [25] = "Inappropriate ioctl for device",
    [26] = "Text file busy",
    [27] = "File too large",
    [28] = "No space left on device",
    [29] = "Illegal seek",
    [30] = "Read-only file system",
    [31] = "Too many links",
    [32] = "Broken pipe",
    [33] = "Numerical argument out of domain",
    [34] = "Numerical result out of range",
    [35] = "Resource deadlock avoided",
    [36] = "File name too long",
    [37] = "No record locks available",
    [38] = "Function not implemented",
    [39] = "Directory not empty",
    [40] = "Too many symbolic links encountered",
    [42] = "No message of desired type",
    [43] = "Identifier removed",
    [44] = "Channel number out of range",
    [45] = "Level 2 not synchronized",
    [46] = "Level 3 halted",
    [47] = "Level 3 reset",
    [48] = "Link number out of range",
    [49] = "Protocol driver not attached",
    [50] = "No CSI structure available",
    [51] = "Level 2 halted",
    [52] = "Invalid exchange",
    [53] = "Invalid request descriptor",
    [54] = "Exchange full",
    [55] = "No anode",
    [56] = "Invalid request code",
    [57] = "Invalid slot",
    [59] = "Bad font file format",
    [60] = "Device not a stream",
    [61] = "No data available",
    [62] = "Timer expired",
    [63] = "Out of streams resources",
    [64] = "Machine is not on the network",
    [65] = "Package not installed",
    [66] = "Object is remote",
    [67] = "Link has been severed",
    [68] = "Advertise error",
    [69] = "Srmount error",
    [70] = "Communication error on send",
    [71] = "Protocol error",
    [72] = "Multihop attempted",
    [73] = "RFS specific error",
    [74] = "Not a data message",
    [75] = "Value too large for defined data type",
    [76] = "Name not unique on network",
    [77] = "File descriptor in bad state",
    [78] = "Remote address changed",
    [79] = "Cannot access needed shared library",
    [80] = "Corrupted shared library",
    [81] = ".lib section in a.out corrupted",
    [82] = "Too many shared libraries",
    [83] = "Cannot exec a shared library",
    [84] = "Illegal byte sequence",
    [85] = "Interrupted system call should restart",
    [86] = "Streams pipe error",
    [95] = "Operation not supported on endpoint",
    [96] = "Protocol family not supported",
    [97] = "Address family not supported",
    [98] = "Address already in use",
    [99] = "Cannot assign requested address",
    [100]= "Network is down",
    [101]= "Network unreachable",
    [102]= "Network dropped connection on reset",
    [103]= "Connection aborted",
    [104]= "Connection reset by peer",
    [105]= "No buffer space available",
    [106]= "Transport endpoint is already connected",
    [107]= "Transport endpoint is not connected",
    [108]= "Cannot send after shutdown",
    [109]= "Too many references",
    [110]= "Connection timed out",
    [111]= "Connection refused",
    [112]= "Host is down",
    [113]= "Host unreachable",
    [114]= "Operation already in progress",
    [115]= "Operation now in progress",
};

/*Core Local*/
static const char*
TraceBackMap[MaxTraceback]=
{
    "General",
    
    "Core/Headers/Boot/PreBoot.h->Limine_REQUEST",
    
    "Core/Main_KExports.c->LookUpKExport",
    
    "Core/Main_Errors.c->RegisterErrorContext",

    "Core/VirtualFileSystem/*->VFS_KickStart",
    "Core/VirtualFileSystem/*->VFS_PowerOff",
    "Core/VirtualFileSystem/*->VFS_RegisterFileSystem",
    "Core/VirtualFileSystem/*->VFS_UnRegisterFileSystem",
    "Core/VirtualFileSystem/*->VFS_FindFileSystem",
    "Core/VirtualFileSystem/*->VfsListFs",
    "Core/VirtualFileSystem/*->VFS_Mount",
    "Core/VirtualFileSystem/*->VFS_UnMount",
    "Core/VirtualFileSystem/*->VFS_ChangeRoot",
    "Core/VirtualFileSystem/*->VFS_BindMount",
    "Core/VirtualFileSystem/*->VFS_MoveMount",
    "Core/VirtualFileSystem/*->VFS_ReMount",
    "Core/VirtualFileSystem/*->VFS_Resolve",
    "Core/VirtualFileSystem/*->VFS_ResolveAt",
    "Core/VirtualFileSystem/*->VFS_LookUp",
    "Core/VirtualFileSystem/*->VFS_MakePath",
    "Core/VirtualFileSystem/*->VFS_RealPath",
    "Core/VirtualFileSystem/*->VFS_Open",
    "Core/VirtualFileSystem/*->VFS_OpenAt",
    "Core/VirtualFileSystem/*->VFS_Close",
    "Core/VirtualFileSystem/*->VFS_Read",
    "Core/VirtualFileSystem/*->VFS_Write",
    "Core/VirtualFileSystem/*->VFS_LSeek",
    "Core/VirtualFileSystem/*->VFS_IOControl",
    "Core/VirtualFileSystem/*->VFS_FSync",
    "Core/VirtualFileSystem/*->VFS_FStats",
    "Core/VirtualFileSystem/*->VFS_Stats",
    "Core/VirtualFileSystem/*->VFS_ReadDirectory",
    "Core/VirtualFileSystem/*->VFS_ReadDirectoryF",
    "Core/VirtualFileSystem/*->VFS_Create",
    "Core/VirtualFileSystem/*->VFS_UnLink",
    "Core/VirtualFileSystem/*->VFS_MakeDirectory",
    "Core/VirtualFileSystem/*->VFS_RemoveDirectory",
    "Core/VirtualFileSystem/*->VFS_SymbolLink",
    "Core/VirtualFileSystem/*->VFS_ReadLink",
    "Core/VirtualFileSystem/*->VFS_Link",
    "Core/VirtualFileSystem/*->VFS_ReName",
    "Core/VirtualFileSystem/*->VFS_ChangeMode",
    "Core/VirtualFileSystem/*->VFS_ChangeOwner",
    "Core/VirtualFileSystem/*->VFS_Truncate",
    "Core/VirtualFileSystem/*->VFS_NodeReferenceIncrement",
    "Core/VirtualFileSystem/*->VFS_NodeReferenceDecrement",
    "Core/VirtualFileSystem/*->VFS_NodeGetAttribute",
    "Core/VirtualFileSystem/*->VFS_NodeSetAttribute",
    "Core/VirtualFileSystem/*->VFS_DentryInvalidate",
    "Core/VirtualFileSystem/*->VFS_DentryRevalidate",
    "Core/VirtualFileSystem/*->VFS_DentryAttach",
    "Core/VirtualFileSystem/*->VFS_DentryDetach",
    "Core/VirtualFileSystem/*->VFS_DentryName",
    "Core/VirtualFileSystem/*->VFS_SetWorkingDirectory",
    "Core/VirtualFileSystem/*->VFS_GetWorkingDirectory",
    "Core/VirtualFileSystem/*->VFS_SetRoot",
    "Core/VirtualFileSystem/*->VFS_GetRoot",
    "Core/VirtualFileSystem/*->VFS_SetUnMask",
    "Core/VirtualFileSystem/*->VFS_GetUnMask",
    "Core/VirtualFileSystem/*->VFS_NotifySubscribe",
    "Core/VirtualFileSystem/*->VFS_NotifyUnSubscribe",
    "Core/VirtualFileSystem/*->VFS_NotifyPoll",
    "Core/VirtualFileSystem/*->VFS_Access",
    "Core/VirtualFileSystem/*->VFS_Exists",
    "Core/VirtualFileSystem/*->VFS_IsDirectory",
    "Core/VirtualFileSystem/*->VFS_IsFile",
    "Core/VirtualFileSystem/*->VFS_IsSymbolLink",
    "Core/VirtualFileSystem/*->VFS_Copy",
    "Core/VirtualFileSystem/*->VFS_Move",
    "Core/VirtualFileSystem/*->VFS_ReadAll",
    "Core/VirtualFileSystem/*->VFS_WriteAll",
    "Core/VirtualFileSystem/*->VFS_MountTableEnumerate",
    "Core/VirtualFileSystem/*->VFS_MountTableFind",
    "Core/VirtualFileSystem/*->VFS_NodePath",
    "Core/VirtualFileSystem/*->VFS_NodeName",
    "Core/VirtualFileSystem/*->VFS_AllocateName",
    "Core/VirtualFileSystem/*->VFS_FreeName",
    "Core/VirtualFileSystem/*->VFS_JoinPath",
    "Core/VirtualFileSystem/*->VFS_SetFlag",
    "Core/VirtualFileSystem/*->VFS_ClearFlag",
    "Core/VirtualFileSystem/*->VFS_GetFlags",
    "Core/VirtualFileSystem/*->VFS_SyncAll",
    "Core/VirtualFileSystem/*->VFS_PruneCaches",
    "Core/VirtualFileSystem/*->VFS_RegisterDeviceNode",
    "Core/VirtualFileSystem/*->VFS_UnRegisterDeviceNode",
    "Core/VirtualFileSystem/*->VFS_RegisterPseudoFileSystem",
    "Core/VirtualFileSystem/*->VFS_UnRegisterPseudoFileSystem",
    "Core/VirtualFileSystem/*->VFS_SetDefaultFileSystem",
    "Core/VirtualFileSystem/*->VFS_GetDefaultFileSystem",
    "Core/VirtualFileSystem/*->VFS_SetMaxName",
    "Core/VirtualFileSystem/*->VFS_GetMaxName",
    "Core/VirtualFileSystem/*->VFS_SetMaxPath",
    "Core/VirtualFileSystem/*->VFS_GetMaxPath",
    "Core/VirtualFileSystem/*->VFS_SetDirectoryCacheLimit",
    "Core/VirtualFileSystem/*->VFS_GetDirectoryCacheLimit",
    "Core/VirtualFileSystem/*->VFS_SetFileCacheLimit",
    "Core/VirtualFileSystem/*->VFS_GetFileCacheLimit",
    "Core/VirtualFileSystem/*->VFS_SetIOBlockSize",
    "Core/VirtualFileSystem/*->VFS_GetIOBlockSize",
    "Core/VirtualFileSystem/*->AllocateDirectoryEntry",
    "Core/VirtualFileSystem/*->Walk",

    "Core/System/*->System_KickStart",
    "Core/System/*->System_PowerOff",
    "Core/System/*->System_CreateNode",
    "Core/System/*->System_DeleteNode",
    "Core/System/*->System_FindNode",
    "Core/System/*->System_AttachNode",
    "Core/System/*->System_DetachNode",
    "Core/System/*->System_GetRoot",
    "Core/System/*->System_CreateFile",
    "Core/System/*->System_CreateDirectory",
    "Core/System/*->System_Open",
    "Core/System/*->System_Close",
    "Core/System/*->System_Read",
    "Core/System/*->System_Write",
    "Core/System/*->System_ReadDirectory",
    "Core/System/*->System_LookUp",
    "Core/System/*->System_Stat",
    "Core/System/*->System_GetAttribute",
    "Core/System/*->System_SetAttribute",
    "Core/System/*->System_StatFileSystem",
    "Core/System/*->System_Sync",
    "Core/System/*->System_Release",
    "Core/System/*->System_SetContext",
    "Core/System/*->System_GetContext",
    "Core/System/*->System_GetContextSize",
    "Core/System/*->System_Walk",
    "Core/System/*->System_Mount",
    "Core/System/*->System_UnMount",
    "Core/System/*->System_RegisterFileSystem",
    "Core/System/*->System_UnRegisterFileSystem",
    "Core/System/*->System_Ioctl",
};

/*Another helper but to map the enum code to a error string map*/
static inline const char*
MapError(SYSTEM_ERROR* Error)
{
    if (Error->ErrorCode < 0)
    {
        Error->ErrorCode = -Error->ErrorCode;
    }
    if (Error->ErrorCode >= MaxErrors)
    {
        return "Bad Error";
    }
    return ErrorMap[Error->ErrorCode];
}

/*Another helper but to map the traceback code to the location of the error from map*/
static inline const char*
CORE_TraceError(SYSTEM_ERROR* Error)
{
    if (Error->ErrorCode < 0)
    {
        Error->ErrorCode = -Error->ErrorCode;
    }
    if (Error->ErrorCode >= MaxErrors)
    {
        return "Bad Error";
    }
    if (Error->TraceBack >= MaxTraceback)
    {
        return "Bad TraceBack";
    }
    return TraceBackMap[Error->TraceBack];
}

/*Per module*/
typedef struct ERROR_KEYS
{
    const char* ModuleName;
    int TracebackBase;
    int TracebackCount;

    /*Operations*/
    const char* (*TraceMapper)(int);

    struct ERROR_KEYS* Next;
} ERROR_KEYS;

typedef struct
{
    ERROR_KEYS* Head;
    ERROR_KEYS* Tail;

    int NextModuleBase;  /* Next available base ID */
} ERROR_KEYS_REGISTRY;

extern ERROR_KEYS_REGISTRY ErrorKeysRegistry;

int RegisterErrorKeys(const char*, const char* (*TraceMapper)(int), int, SYSTEM_ERROR*);
const char* TraceError(SYSTEM_ERROR*);