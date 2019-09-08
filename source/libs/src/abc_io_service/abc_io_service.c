#include "abc_io_service/abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

bool
abc_ioService_write(const int value, const char *const restrict pFileName)
{
    if (NULL == pFileName)
    {
        ABC_LOG_ERR("Invalid filename");

        return false;
    }

    errno = 0;

    FILE *const restrict pFile = fopen(pFileName, "w");
    if (NULL == pFile)
    {
        ABC_LOG_ERR("Failed to open the file `%s` due to: %s",
                    pFileName, strerror(errno));

        return false;
    }

    bool isReturnOK = true;

    const int numWrittenBytes = fprintf(pFile, "%d", value);
    if (numWrittenBytes < 0)
    {
        ABC_LOG_ERR("Failed to write to file `%s` due to: %s",
                    pFileName, strerror(errno));

        isReturnOK = false;
    }
    else if (numWrittenBytes == 0)
    {
        ABC_LOG_ERR("Nothing written to the file `%s` due to: %s",
                    pFileName, strerror(errno));

        isReturnOK = false;
    }
    else
    {
        ABC_LOG("Written %d to file `%s`", value, pFileName);
    }

    errno = 0;

    if (0 != fclose(pFile))
    {
        ABC_LOG_ERR("Failed to close file `%s` due to: %s. "
                    "File is left in an undefined state.",
                    pFileName, strerror(errno));

        return false;
    }

    return isReturnOK;
}

static inline bool
strToInt(int *const restrict pResult, const char *const restrict pStr)
{
    assert(pResult && pStr);

    errno = 0;

    char *pEnd;
    const long readNum = strtol(pStr, &pEnd, 10);
    if (errno)
    {
        ABC_LOG_ERR("Failed to convert string to long due to: %s", strerror(errno));

        return false;
    }

    // Check if anything was read.
    if (pEnd == pStr)
    {
        ABC_LOG_ERR("Failed to convert string to long as nothing was read");

        return false;
    }

    // A full conversion occurs when pEnd is null or '\n'.
    if (*pEnd && *pEnd != '\n')
    {
        ABC_LOG_ERR("Failed to convert the string fully to long");

        return false;
    }

    if (readNum > INT_MAX || readNum < INT_MIN)
    {
        ABC_LOG_ERR("The read value (%lu) is too large", readNum);

        return false;
    }

    *pResult = (int)readNum;

    return true;
}

bool
abc_ioService_read(int *const restrict pValue,
                   const char *const restrict pFileName)
{
    if (NULL == pFileName || NULL == pValue)
    {
        ABC_LOG_ERR("Bad filename = %p or bad ret value = %p",
                    (const void *)pFileName, (void *)pValue);

        return false;
    }

    FILE *const restrict pFile = fopen(pFileName, "r");

    if (NULL == pFile)
    {
        ABC_LOG_ERR("Failed to open the file due to: %s", strerror(errno));

        return false;
    }

    bool isReturnOK = true;

    char readLine[10];

    if (NULL == fgets(readLine, sizeof(readLine), pFile))
    {
        ABC_LOG_ERR("Reached EOF too early");

        isReturnOK = false;
    }
    else if (errno)
    {
        ABC_LOG_ERR("Failed to read the file due to: %s", strerror(errno));

        isReturnOK = false;
    }
    else
    {
        ABC_LOG("Read `%s` from file %s", readLine, pFileName);
    }

    errno = 0;

    if (0 != fclose(pFile))
    {
        ABC_LOG_ERR("Failed to close file `%s` due to: %s. "
                    "File is left in an undefined state.",
                    pFileName, strerror(errno));

        return false;
    }

    if (!isReturnOK)
    {
        return false;
    }

    readLine[9] = '\0';
    if (!strToInt(pValue, readLine))
    {
        return false;
    }

    return true;
}
