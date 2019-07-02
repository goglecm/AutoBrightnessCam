#ifndef AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#define ABC_LOGGING_ON 1

extern bool g_isFirstLog;
extern FILE *g_pLogFile;
extern const char g_logFilename[];

#define ABC_LOG_ERR(...) do { \
    g_pLogFile = fopen(g_logFilename, "a"); \
    if (g_pLogFile) \
    { \
        fprintf(g_pLogFile, "\nERROR: %s: ", __func__); \
        fprintf(g_pLogFile, __VA_ARGS__) ; \
        fclose(g_pLogFile); \
    } \
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
    if (ABC_LOGGING_ON) { \
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
    }\
} while (0)

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_LOGGING_SERVICE_H
