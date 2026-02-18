#include <__KCONF.h>
#include <VirtualFileSystem.h>
#include <Errors.h>

/*THIS IS A MODULARUS CORE STANDARD FILE WITH A STANDARD NAME OF "STANDARD_Init"
  The job of this file is to handle ITS own modules and init sequence.*/

SYSTEM_ERROR Err;
SYSTEM_ERROR* Error = &Err;

int _start(void) /*STANDARD NAME "_start"*/
{
    /*Do stuff*/
    return 0;
}

int _exit(void) /*STANDARD NAME "_exit"*/
{
    /*End stuff*/
    return 0;
}