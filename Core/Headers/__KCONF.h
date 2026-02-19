#pragma once

#include <CTools.h>
#include <Types.h>
#include <KernelCLibrary.h>

/*========================================*/

/*
    PreBoot compile time options
*/
/*__>*/ /*BootVendors*/
/*|_>*/ #define BOOTVENDOR_Limine

/*========================================*/

/*
    Types source
*/
/*__>*/ /*Standard Types Toggle*/
/*|_>*/ #define StandardLIBC

/*========================================*/

/*
    Limits
*/
/*__>*/ /*Modules*/
/*|_>*/ #define MaxModules 512

/*========================================*/

/*
    Toggles
*/
/*__>*/ /*Misc Toggles*/
/*|_>*/ #define BUILTINS
/*|_>*/ // #define TESTING
/*|_>*/ #define TRACEBACK
/*|*/
/*|_>*/ /*BuiltIns Toggles*/
/*|_>*/ #define BUILTIN_UART
/*|_>*/ #define BUILTIN_Formatter
/*|_>*/ #define BUILTIN_Loader
/*|_>*/ #define BUILTIN_Linker
/*|*/
/*|_>*/ /*Log Toggles*/
/*|_>*/ #define DEBUGS
/*|_>*/ #define ERRORS
/*|_>*/ #define INFORMATIONS
/*|_>*/ #define WARNS
/*|_>*/ #define SUCCESSES

/*========================================*/
