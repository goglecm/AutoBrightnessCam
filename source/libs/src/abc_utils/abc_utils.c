#include "abc_utils/abc_utils.h"

#include "abc_logging_service/abc_logging_service.h"

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

bool
abc_utils_strToInt(int *const restrict pResult, const char *const pStr)
{
    if (NULL == pResult)
    {
        ABC_LOG_ERR("Bad result ptr");

        return false;
    }

    if (NULL == pStr)
    {
        ABC_LOG_ERR("Bad string ptr");

        return false;
    }

    // Limiting to 16 chars.
    static const int s_MAX_LEN = 16;
    const int strLen = (int)strnlen(pStr, s_MAX_LEN + 1);
    if (strLen <= 0 || strLen > s_MAX_LEN)
    {
        ABC_LOG_ERR("Bad string length");

        return false;
    }

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
