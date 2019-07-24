#ifndef AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#ifndef ABC_LOGGING_ON

#define ABC_LOGGING_ON 1

#endif // #ifndef ABC_LOGGING_ON

#ifndef ABC_STDOUT_LOGGING_ON

#define ABC_STDOUT_LOGGING_ON 0

#endif // #ifndef ABC_LOGGING_ON

extern bool g_isFirstLog;
extern FILE *g_pLogFile;
extern char g_logFilename[512];

bool
abc_loggingService_setLogName(const char *pLogName);

#define ABC_LOG_ERR(...) do { \
    g_pLogFile = fopen(g_logFilename, "a"); \
    if (g_pLogFile) \
    { \
        fprintf(g_pLogFile, "\nERROR: %s: ", __func__); \
        fprintf(g_pLogFile, __VA_ARGS__) ; \
        fclose(g_pLogFile); \
    } \
} while (0)

#define ABC_LOG_STDOUT_ERR(...) do { \
    printf("\nERROR: %s: ", __func__); \
    printf(__VA_ARGS__); \
    fflush(stdout); \
} while (0)

#define ABC_LOG_STDOUT(...) if (ABC_STDOUT_LOGGING_ON) do { \
    printf("\n%s: ", __func__); \
    printf(__VA_ARGS__); \
} while (0)

#define ABC_LOG_WRN(...) do { \
    g_pLogFile = fopen(g_logFilename, "a"); \
    if (g_pLogFile) \
    { \
        fprintf(g_pLogFile, "\nWARNING: %s: ", __func__); \
        fprintf(g_pLogFile, __VA_ARGS__) ; \
        fclose(g_pLogFile); \
    } \
} while (0)

#define ABC_LOG(...) if (ABC_LOGGING_ON) do { \
    if (g_isFirstLog) { \
        g_pLogFile = fopen(g_logFilename, "w"); \
        if (g_pLogFile) \
        { \
            fprintf(g_pLogFile, "Starting logs\n\n"); \
            g_isFirstLog = false; \
            fclose(g_pLogFile); \
        } \
    } \
    g_pLogFile = fopen(g_logFilename, "a"); \
    if (g_pLogFile) \
    { \
        fprintf(g_pLogFile, "\n%s: ", __func__); \
        fprintf(g_pLogFile, __VA_ARGS__) ; \
        fclose(g_pLogFile); \
    } \
} while (0)

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H
