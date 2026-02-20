#include <Errors.h>

/*Local*/
#include <BuiltIns/Logger/Formatter.h>
#include <BuiltIns/Logger/Emitter.h>

void
_PError(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[    ERROR    ]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            ProcessFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
_PWarn(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[   WARNING   ]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            ProcessFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
_PInfo(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[ INFORMATION ]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            ProcessFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
_PDebug(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[    DEBUG    ]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            ProcessFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}

void
_PSuccess(const char* Format, ...)
{
    if (Probe4Error(Format) || !Format)
    {
        Format = "(null)";
    }

    PutString("[   SUCCESS   ]: ");

    __builtin_va_list Arguments;
    __builtin_va_start(Arguments, Format);

    while (*Format)
    {
        if (*Format == '%')
        {
            Format++;
            ProcessFormatSpecifier(&Format, &Arguments);
        }
        else
        {
            PutChar(*Format);
            Format++;
        }
    }

    __builtin_va_end(Arguments);
}