#include "abc_io_service/abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"
#include "abc_utils/abc_utils.h"

#include <sys/stat.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


// Excluding null terminator.
#define MAX_STR_LEN 128

// Excluding null terminator.
#define MAX_FILENAME_LENGTH 512


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

static inline bool
readLineStartingWith(
        const char *const restrict pStartStr,
        char *const restrict pRetStr,
        const int retStrBufMaxLen,
        const char *const restrict pFileName)
{
    // Down cast and using strlen (instead of strnlen) as we've range checked
    // the length of the starting string.
    const int startStrLen = (int)strlen(pStartStr);

    assert(pStartStr &&
            pRetStr &&
            pFileName &&
            retStrBufMaxLen > startStrLen + 1);


    // # Open the file.

    FILE *const restrict pFile = fopen(pFileName, "r");

    if (NULL == pFile)
    {
        ABC_LOG_ERR("Failed to open the file due to: %s", strerror(errno));

        return false;
    }


    bool errorsEncountered = false;

    ABC_LOG("Starting string is `%s`", pStartStr);

    // # Search for the beginning of the start string and skip over it.
    int charsMatched = 0;
    int readChar;
    int charsReadInCurrentLine = 0;
    while (charsMatched != startStrLen || charsReadInCurrentLine != startStrLen)
    {
        // ## Read the next char.
        errno = 0;
        readChar = fgetc(pFile);

        if (0 != errno)
        {
            ABC_LOG_ERR("Failed to read file due to: %s", strerror(errno));

            break;
        }

        if (readChar == EOF)
        {
            break;
        }


        // ## Update char counters.
        if (readChar == '\n')
        {
            charsReadInCurrentLine = 0;
        }
        else
        {
            charsReadInCurrentLine++;
        }


        // ## Check if the char matches the starting string.
        if (charsMatched < startStrLen && pStartStr[charsMatched] == readChar)
        {
            charsMatched++;
        }
        else
        {
            charsMatched = 0;
        }

        ABC_LOG("Checking char `%c`(0x%x), charsMatched %d, "
                "charsReadInCurrentLine %d, start len %d",
                readChar,
                readChar,
                charsMatched,
                charsReadInCurrentLine,
                startStrLen);
    }


    // # Handle the case when reaching the end of file prematurely.
    if (charsMatched != startStrLen)
    {
        ABC_LOG_ERR("Failed to find starting string");

        errorsEncountered = true;
    }


    // # Found the line, now read the remainder of the it.
    if (!errorsEncountered)
    {
        const int lineRemBufSize = retStrBufMaxLen - startStrLen;
        char lineRemStr[lineRemBufSize];

        if (NULL == fgets(lineRemStr, lineRemBufSize, pFile))
        {
            ABC_LOG_ERR("Reached EOF too early: %s", strerror(errno));

            errorsEncountered = true;
        }
        else if (errno)
        {
            ABC_LOG_ERR("Failed to read the file due to: %s", strerror(errno));

            errorsEncountered = true;
        }
        else
        {
            ABC_LOG("Read remainder `%s` from file %s", lineRemStr, pFileName);

            // Using strlen (instead of strnlen) as it has already been bounded
            // by fgets.
            memcpy(pRetStr, pStartStr, startStrLen);
            memcpy(pRetStr + startStrLen, lineRemStr, strlen(lineRemStr) + 1);

            ABC_LOG("Resultant line is `%s`", pRetStr);
        }
    }


    // # Close the file.
    errno = 0;
    if (0 != fclose(pFile))
    {
        ABC_LOG_ERR("Failed to close file `%s` due to: %s. "
                    "File is left in an undefined state.",
                    pFileName, strerror(errno));

        errorsEncountered = true;
    }

    return ! errorsEncountered;
}

bool
abc_ioService_readLineStartingWith(
        const char *const restrict pStartStr,
        char *const restrict pRetStr,
        const int retStrBufMaxLen,
        const char *const restrict pFileName)
{
    // # Pointer validation.

    if (NULL == pStartStr)
    {
        ABC_LOG_ERR("Bad start string");

        return false;
    }

    if (NULL == pRetStr)
    {
        ABC_LOG_ERR("Bad return string");

        return false;
    }

    if (NULL == pFileName)
    {
        ABC_LOG_ERR("Bad filename");

        return false;
    }


    // # Range checking.

    const size_t startStrLen = strnlen(pStartStr, MAX_STR_LEN + 1);
    if (startStrLen < 1 || startStrLen >= MAX_STR_LEN)
    {
        ABC_LOG_ERR("Bad start string length");

        return false;
    }

    const size_t filenameLen = strnlen(pFileName, MAX_FILENAME_LENGTH + 1);
    if (filenameLen < 1 || filenameLen >= MAX_FILENAME_LENGTH)
    {
        ABC_LOG_ERR("Bad filename length");

        return false;
    }

    if (retStrBufMaxLen < 1 || retStrBufMaxLen > MAX_STR_LEN)
    {
        ABC_LOG_ERR("Bad return string max length %d", retStrBufMaxLen);

        return false;
    }


    // # Handle the easy cases (not requiring file reads).

    // Down casting as we've just range checked startStrLen.
    if (retStrBufMaxLen <= (int)(startStrLen + 1))
    {
        memcpy(pRetStr, pStartStr, retStrBufMaxLen);

        pRetStr[retStrBufMaxLen - 1] = '\0';

        ABC_LOG("Returning the starting string (or a portion of it)  %s as the "
                "max length is %d", pRetStr, retStrBufMaxLen);

        return true;
    }


    // # Handle the general case (requiring file reads).

    return readLineStartingWith(pStartStr, pRetStr, retStrBufMaxLen, pFileName);
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
