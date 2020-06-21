#ifndef AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>


#ifndef ABC_LOGGING_ON

#error "ABC_LOGGING_ON is not defined"

#endif // ABC_LOGGING_ON


#if ABC_LOGGING_ON != 0 && ABC_LOGGING_ON != 1

#error "Invalid value for ABC_LOGGING_ON"

#endif // ABC_LOGGING_ON


#if ABC_LOGGING_ON == 1

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

#define ABC_LOG_STDOUT(...) do { \
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

#define ABC_LOG(...) do { \
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

#else

#define ABC_LOG_ERR(...) ;
#define ABC_LOG_STDOUT_ERR(...) ;
#define ABC_LOG_STDOUT(...) ;
#define ABC_LOG_WRN(...) ;
#define ABC_LOG(...) ;

#endif // #if ABC_LOGGING_ON == 1

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H
