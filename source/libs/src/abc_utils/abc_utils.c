#include "abc_utils/abc_utils.h"

#include "abc_logging_service/abc_logging_service.h"

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// # Up to 2^32, including minus sign.
#define MAX_INT_DEC_CHARS_LEN 11

bool
abc_utils_strToInt(int *const restrict pResult, const char *const pStr)
{
    // Validate pointers.
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

    // Range check the string to convert.
    const int strLen = (int)strnlen(pStr, MAX_INT_DEC_CHARS_LEN + 1);
    if (strLen <= 0 || strLen > MAX_INT_DEC_CHARS_LEN)
    {
        ABC_LOG_ERR("Bad string length");

        return false;
    }

    // Convert the string to long.
    errno = 0;
    char *pEnd;
    const long readNum = strtol(pStr, &pEnd, 10);

    if (errno)
    {
        ABC_LOG_ERR("Failed to convert string to long due to: `%s`", strerror(errno));

        return false;
    }

    // Check if anything was read from the string.
    if (pEnd == pStr)
    {
        ABC_LOG_ERR("Failed to convert string to long as nothing was read from it");

        return false;
    }

    // A full conversion occurs when pEnd points to the char past the
    // string (i.e. NULL).
    if (*pEnd != '\0')
    {
        ABC_LOG_ERR("Failed to convert the string fully to long");

        return false;
    }

    // Range check the result.
    if (readNum > INT_MAX || readNum < INT_MIN)
    {
        ABC_LOG_ERR("The read value (%ld) is too large", readNum);

        return false;
    }

    // Safely downcast to int.
    *pResult = (int)readNum;

    return true;
}
