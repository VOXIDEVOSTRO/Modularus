#include <__KCONF.h>
#include <Errors.h>

#include <VirtualFileSystem.h>
#include <System.h>/*sysfs++*/

#ifdef BUILTINS
    #ifdef BUILTIN_UART
        #include <BuiltIns/Device/UART.h>
    #endif

    #ifdef BUILTIN_Formatter
        #include <BuiltIns/Logger/Emitter.h>
        #include <BuiltIns/Logger/Formatter.h>
    #endif

    #ifdef BUILTIN_Linker
        #include <BuiltIns/Linker/LinkerELF.h>
    #endif

    #ifdef BUILTIN_Loader
        #include <BuiltIns/Loader/Loader.h>
    #endif
#endif

SYSTEM_ERROR Err;
SYSTEM_ERROR* Error = &Err;
    
void KernelMain(void)
{
    /*STANDARD*/
    VFS_KickStart(Error);

    /*STANDARD*/
    System_KickStart(Error/*As Root "/"*/);

    /*STANDARD*/
    VFS_Mount("", "/", "sysfs++", 0, 0, Error);

    /*BuiltIns*/
    #ifdef BUILTINS
        #ifdef BUILTIN_UART
            UART_KickStart(Error);
        #endif

        #ifdef BUILTIN_Formatter
            Emitter_KickStart(Error);
        #endif

        #ifdef BUILTIN_Loader
            Loader_GetModules(Error); /*So the /loader can register itself*/
        #endif

        #ifdef BUILTIN_Linker
            Linker_Init(Error); /*/linker*/
        #endif
    #endif

    #ifdef TESTING

        #ifdef BUILTIN_Formatter
            KrnPrintf("\nHello World!\n");
        #endif
        
        #ifdef BUILTIN_Loader
            FILE* LoaderFile = VFS_Open("/loader", VFS_OpenFlag_WRITEONLY, Error);
            if (Probe4Error(LoaderFile) || !LoaderFile)
            {
                goto Error;
            }

            LOADED_MODULE TestModule;
            LOADER_COMMAND_GET_ARGUMENTS TestModuleRequest =
            {
                .Name = "Test.ko",
                .Out = &TestModule
            };

            if (VFS_IOControl(LoaderFile, LoaderCommand_GET, &TestModuleRequest, Error) != GeneralOK)
            {
                goto Error;
            }
        #endif

        #ifdef BUILTIN_Linker
            #ifdef BUILTIN_Loader
                FILE* LinkerFile = VFS_Open("/linker", VFS_OpenFlag_WRITEONLY, Error);
                if (Probe4Error(LinkerFile) || !LinkerFile)
                {
                    goto Error;
                }
                
                if (Probe4Error(TestModule.Address) || !TestModule.Address)
                {
                    goto Error;
                }

                if (VFS_IOControl(LinkerFile, LinkerCommand_LINK, TestModule.Address, Error) != GeneralOK)
                {
                    goto Error;
                }
            #endif
            if (VFS_IOControl(LinkerFile, LinkerCommand_RUN, NULL, Error) != GeneralOK)
            {
                goto Error;
            }
        #endif

    #else

        /*STANDARD*/
        #ifdef BUILTIN_Loader
            FILE* LoaderFile = VFS_Open("/loader", VFS_OpenFlag_WRITEONLY, Error);
            if (Probe4Error(LoaderFile) || !LoaderFile)
            {
                goto Error;
            }

            LOADED_MODULE STANDARD_InitModule;
            LOADER_COMMAND_GET_ARGUMENTS STANDARD_InitModuleRequest =
            {
                .Name = "STANDARD_Init.ko",
                .Out = &STANDARD_InitModule
            };

            if (VFS_IOControl(LoaderFile, LoaderCommand_GET, &STANDARD_InitModuleRequest, Error) != GeneralOK)
            {
                goto Error;
            }
        #endif

        #ifdef BUILTIN_Linker
            #ifdef BUILTIN_Loader
                FILE* LinkerFile = VFS_Open("/linker", VFS_OpenFlag_WRITEONLY, Error);
                if (Probe4Error(LinkerFile) || !LinkerFile)
                {
                    goto Error;
                }
                
                if (Probe4Error(STANDARD_InitModule.Address) || !STANDARD_InitModule.Address)
                {
                    goto Error;
                }

                if (VFS_IOControl(LinkerFile, LinkerCommand_LINK, STANDARD_InitModule.Address, Error) != GeneralOK)
                {
                    goto Error;
                }
            #endif
            if (VFS_IOControl(LinkerFile, LinkerCommand_RUN, NULL, Error) != GeneralOK)
            {
                goto Error;
            }
        #endif

    #endif

    for(;;)
    {
        __asm__("hlt");
    }
    
Error:
    for(;;)
    {
        __asm__("hlt");
    }
}