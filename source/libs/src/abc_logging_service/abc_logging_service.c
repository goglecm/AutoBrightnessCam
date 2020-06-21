#include "abc_logging_service/abc_logging_service.h"

#if ABC_LOGGING_ON == 1


#include <stddef.h>
#include <string.h>


bool
g_isFirstLog = true;

FILE
*g_pLogFile = NULL;


#ifndef ABC_LOGGING_DEFAULT_FILENAME

#error "ABC_LOGGING_DEFAULT_FILENAME is not defined"

#endif


char
g_logFilename[512] = ABC_LOGGING_DEFAULT_FILENAME;


bool
abc_loggingService_setLogName(const char *const restrict pLogName)
{
    if (NULL == pLogName)
    {
        ABC_LOG_STDOUT_ERR("failed to set log name path due to invalid log name");

        return false;
    }

    if (strnlen(pLogName, sizeof(g_logFilename)) == sizeof(g_logFilename))
    {
        ABC_LOG_STDOUT_ERR("failed to set log name path as it exceeds the required length");

        return false;
    }

    ABC_LOG_STDOUT("logfile name is %s\n", pLogName);

    g_isFirstLog = true;

    ABC_LOG_STDOUT("old path is %s\n", g_logFilename);

    strncpy(g_logFilename, pLogName, sizeof(g_logFilename) - 1);

    ABC_LOG_STDOUT("new path is %s\n", g_logFilename);

    return true;
}

#endif // #if ABC_LOGGING_ON == 1
