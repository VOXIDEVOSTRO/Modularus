#include <__KCONF.h>
#include <Errors.h>
#include <KExports.h>

ERROR_KEYS_REGISTRY ErrorKeysRegistry =
{
    .Head = NULL,
    .Tail = NULL,
    .NextModuleBase = MaxTraceback
};

const ERROR_KEYS* RegisterErrorKeys(const char* ModuleName, const char* (*TraceMapper)(int), int TracebackCount, SYSTEM_ERROR* Error)
{
    #define ErrorOut_RegisterErrorContext(Code) \
        ErrorOut(Error, NULL, Code, FUNC_RegisterErrorKeys)

    static ERROR_KEYS Contexts[MaxModules];
    static int ContextCount = 0;

    if (ContextCount >= MaxModules)
    {
        ErrorOut_RegisterErrorContext(-EOVERFLOW);
        return NULL;
    }

    ERROR_KEYS* Context = &Contexts[ContextCount++];
    Context->ModuleName = ModuleName;
    Context->TracebackCount = TracebackCount;
    Context->TraceMapper = TraceMapper;
    Context->Next = NULL;

    if (!ErrorKeysRegistry.Head)
    {
        ErrorKeysRegistry.Head = Context;
        ErrorKeysRegistry.Tail = Context;
    }
    else
    {
        ErrorKeysRegistry.Tail->Next = Context;
        ErrorKeysRegistry.Tail = Context;
    }

    return Context;
}

/*Both module and core*/
const char* TraceError(SYSTEM_ERROR* Error)
{
    if (!Error)
    {
        return "Bad Error";
    }

    /* Core */
    if (!Error->Context)
    {
        return CORE_TraceError(Error);
    }
    
    /* Module */
    return Error->Context->TraceMapper(Error->TraceBack);
}

/*Exporting here to break a circular dependency, Normally would be inside a declaring header*/
KEXPORT(TraceError)
KEXPORT(RegisterErrorKeys)