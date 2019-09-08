#include "abc_logging_service/abc_logging_service.h"

#include <stddef.h>
#include <string.h>

bool g_isFirstLog = true;

FILE *g_pLogFile = NULL;

#ifndef ABC_LOGGING_PATH
#define ABC_LOGGING_PATH "."
#endif

char g_logFilename[512] = ABC_LOGGING_PATH "/log.log";

bool
abc_loggingService_setLogName(const char *const restrict pLogName)
{
    if (NULL == pLogName)
    {
        ABC_LOG_STDOUT_ERR("failed to set log name path due to invalid log name");

        return false;
    }

    if (strlen(ABC_LOGGING_PATH "/") + 1 + strnlen(pLogName, 512) > 512)
    {
        ABC_LOG_STDOUT_ERR("failed to set log name path as it exceeds the required length");

        return false;
    }

    ABC_LOG_STDOUT("logfile name is %s\n", pLogName);

    g_isFirstLog = true;

    ABC_LOG_STDOUT("old path is %s\n", g_logFilename);

    strncpy(g_logFilename, ABC_LOGGING_PATH "/", sizeof(g_logFilename) - 1);

    strncpy(&g_logFilename[strlen(g_logFilename)], pLogName, sizeof(g_logFilename) - 1);

    ABC_LOG_STDOUT("new path is %s\n", g_logFilename);

    return true;
}
