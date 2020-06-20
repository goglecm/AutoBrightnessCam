#include "abc_io_service/abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"
#include "abc_utils/abc_utils.h"

#include <sys/stat.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

bool
abc_ioService_exists(const char *const restrict pFileName)
{
    struct stat buffer;
    return 0 == stat(pFileName, &buffer);
}

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

bool
abc_ioService_readStr(char *const restrict pBuf,
                      const int bufMaxLen,
                      const char *const restrict pFileName)
{
    if (NULL == pFileName || NULL == pBuf || bufMaxLen < 1 || bufMaxLen > 32)
    {
        ABC_LOG_ERR("Bad filename = %p or bad ret value = %p or max len = %d",
                    (const void *)pFileName, (void *)pBuf, bufMaxLen);

        return false;
    }

    FILE *const restrict pFile = fopen(pFileName, "r");

    if (NULL == pFile)
    {
        ABC_LOG_ERR("Failed to open the file due to: %s", strerror(errno));

        return false;
    }

    bool isReturnOK = true;

    char readLine[bufMaxLen];

    if (NULL == fgets(readLine, bufMaxLen, pFile))
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

    memcpy(pBuf, readLine, strnlen(readLine, bufMaxLen - 1) + 1);

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
    if (!abc_utils_strToInt(pValue, readLine))
    {
        return false;
    }

    return true;
}
