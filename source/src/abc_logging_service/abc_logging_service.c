#include "abc_logging_service/abc_logging_service.h"

bool g_isFirstLog = true;

FILE *g_pLogFile = NULL;

const char g_logFilename[] = "log.log";
