#pragma once

#include <__KCONF.h>

typedef struct
{
    const char* Format;
    void** Arguments;
    int ArgumentIndex;
} FORMATTER_STATE;

typedef struct
{
    int LeftAlign;
    int ShowSign;
    int SpacePrefix;
    int AlternateForm;
    int ZeroPad;
    int Width;
    int Precision;
    int HasPrecision;
    int Length;
} FORMATTER_FLAGS;

#ifdef DEBUGS
    #define PDebug(Format, ...) \
        _PDebug(Format, ##__VA_ARGS__)
#else
    #define PDebug(Format, ...) \
        do {} while (0)
#endif

#ifdef ERRORS
    #define PError(Format, ...) \
        _PError(Format, ##__VA_ARGS__)
#else
    #define PError(Format, ...) \
        do {} while (0)
#endif

#ifdef INFORMATIONS
    #define PInfo(Format, ...) \
        _PInfo(Format, ##__VA_ARGS__)
#else
    #define PInfo(Format, ...) \
        do {} while (0)
#endif

#ifdef WARNS
    #define PWarn(Format, ...) \
        _PWarn(Format, ##__VA_ARGS__)
#else
    #define PWarn(Format, ...) \
        do {} while (0)
#endif

#ifdef SUCCESSES
    #define PSuccess(Format, ...) \
        _PSuccess(Format, ##__VA_ARGS__)
#else
    #define PSuccess(Format, ...) \
        do {} while (0)
#endif

/*Main*/
void KrnPrintf(const char*, ...);
// void KrnPrintfColor(uint32_t, uint32_t, const char*, ...);
void ProcessFormatSpecifier(const char**, __builtin_va_list*);

/*Helpers*/
void PrintInteger(int, int, int);
void PrintUnsigned(uint32_t, int, int);
void PrintString(const char*);
void PrintChar(char);
void PrintPointer(void*);
int  StringLength(const char*);
void ReverseString(char*, int);
void IntegerToString(int, char*, int);
void UnsignedToString(uint32_t, char*, int);
void ProcessInteger(__builtin_va_list*, FORMATTER_FLAGS*, int, int);
void ProcessString(__builtin_va_list*, FORMATTER_FLAGS*);
void ProcessChar(__builtin_va_list*, FORMATTER_FLAGS*);
void ProcessPointer(__builtin_va_list* , FORMATTER_FLAGS*);
void FormatOutput(const char*, FORMATTER_FLAGS*, int, int);
void UnsignedToStringEx(uint64_t, char*, int, int);

/*Logging*/
void _PError(const char*, ...);
void _PWarn(const char*, ...);
void _PInfo(const char*, ...);
void _PDebug(const char*, ...);
void _PSuccess(const char*, ...);