#include "abc_config_service/abc_config_service.h"

#include "abc_logging_service/abc_logging_service.h"
#include "abc_io_service/abc_io_service.h"
#include "abc_utils/abc_utils.h"

#include <assert.h>
#include <string.h>
#include <stddef.h>


// # Host configuration.
#ifndef ABC_CONFIG_DEFAULTS_FILENAME

#error "ABC_CONFIG_DEFAULTS_FILENAME not defined."

#endif // ABC_CONFIG_DEFAULTS_FILENAME


// # Default configuration.
#ifndef ABC_CONFIG_FILENAME

#error "ABC_CONFIG_FILENAME not defined."

#endif // ABC_CONFIG_FILENAME


typedef abc_configService_Key_t abc_Key_t;

static bool
parseConfigEntry(
        const char *const pEntryStr,
        int *const restrict pRetVal)
{
    assert(pEntryStr && pRetVal);

    // # Check if the entry has a value in the key-value pair.
    const char *const pValueSubStr = strchr(pEntryStr, '=');
    if (NULL == pValueSubStr)
    {
        ABC_LOG_ERR("Failed to find the value in the key-value pair");

        return false;
    }

    // # Check for comments in the entry.
    const char *const pCommentSubStr = strchr(pEntryStr, '#');
    int commentLength;
    if (NULL == pCommentSubStr)
    {
        commentLength = 0;
    }
    else
    {
        commentLength = (int)strlen(pCommentSubStr);

        ABC_LOG("Comment length = %d, str is `%s`",
                commentLength, pCommentSubStr);
    }

    // # Check the value length.
    const int valueLength = (int)strlen(pValueSubStr + 1) - commentLength;
    if (valueLength <= 0)
    {
        ABC_LOG_ERR("The value is a comment");

        return false;
    }

    // # Copy the value (without the comment).
    char value[valueLength + 1];
    memcpy(value, pValueSubStr + 1, valueLength);
    value[valueLength] = '\0';

    // # Strip trailing whitespace.
    while (value[strlen(value) - 1] == ' ')
    {
        value[strlen(value) - 1] = '\0';
    }

    // # Convert the value to int.
    ABC_LOG("String to convert is `%s`", value);
    if (!abc_utils_strToInt(pRetVal, value))
    {
        ABC_LOG_ERR("Failed to convert string value `%s` to int",
                pValueSubStr + 1);

        return false;
    }

    return true;
}

static bool
readKeyValue(
        const abc_Key_t key,
        int *const restrict pValue,
        const char *const restrict pFileName)
{
    if (key == ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD)
    {
        const char keyStr[] = "sampling_period";

        char entryStr[128];
        const bool isResultOK =
            abc_ioService_readLineStartingWith(
                    keyStr,
                    entryStr,
                    sizeof(entryStr),
                    pFileName);

        if (isResultOK)
        {
            if (!parseConfigEntry(entryStr, pValue))
            {
                ABC_LOG_ERR("Failed to parse config entry");

                return false;
            }
        }
        else
        {
            ABC_LOG("Failed to read config entry");

            return false;
        }
    }
    else
    {
        ABC_LOG_ERR("Bad key %d", key);

        return false;
    }

    ABC_LOG("Read key %d -> %d", key, *pValue);

    return true;
}

bool
abc_configService_get(const abc_Key_t key, int *const restrict pValue)
{
    if (NULL == pValue)
    {
        ABC_LOG_ERR("Bad value return pointer");

        return false;
    }

    // # Try to read from the host file.
    bool isResultOK = readKeyValue(key, pValue, ABC_CONFIG_FILENAME);

    // # If can't read from host file, try reading from the defaults file.
    if (!isResultOK)
    {
        isResultOK = readKeyValue(key, pValue, ABC_CONFIG_DEFAULTS_FILENAME);

        if (!isResultOK)
        {
            ABC_LOG_ERR("Can't read key %d", key);

            return false;
        }
    }

    ABC_LOG("Setting key %d to %d", key, *pValue);

    return true;
}
