#include "abc_config_service/abc_config_service.h"

#include "abc_logging_service/abc_logging_service.h"
#include "abc_utils/abc_utils.h"
#include "abc_terminal_controller/abc_terminal_controller.h"

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


#define ENTRY_MAX_LEN 256


typedef abc_configService_Key_t abc_Key_t;


static inline bool
isKeyValid(const abc_Key_t key)
{
    return key >= ABC_CONFIG_SERVICE_KEY__FIRST &&
           key <= ABC_CONFIG_SERVICE_KEY__LAST;
}

static inline const char *
keyToStr(const abc_Key_t key)
{
    assert(isKeyValid(key));

    switch (key)
    {
        case ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD:
        {
            static const char keyStr[] = "sampling_period";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_TRANSITION_SMOOTHNESS:
        {
            static const char keyStr[] = "transition_smoothness";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_TRANSITION_PERIOD:
        {
            static const char keyStr[] = "transition_period";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_MAX_BRIGHTNESS:
        {
            static const char keyStr[] = "max_brightness";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_MIN_BRIGHTNESS:
        {
            static const char keyStr[] = "min_brightness";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_DEPEND_ON_BATTERY:
        {
            static const char keyStr[] = "depend_on_battery";
            return keyStr;
        }

        default:
            assert(false && "Bad key");
            return NULL;
    }
}

// Updating length and pointer to point to the value without white space around.
static void
stripPrefixSuffixWhitespace(const char **const ppValue, size_t *const pLength)
{
    assert(ppValue && *ppValue && pLength);

    ABC_LOG("starting length %zu", *pLength);

    if (*pLength == 0)
    {
        return;
    }

    // Skip prefixed white space from the value.
    while (**ppValue == ' '  ||
           **ppValue == '\n' ||
           **ppValue == '\t')
    {
        ABC_LOG("Removing prefix space (0x%x) `%c`", **ppValue, **ppValue);

        (*ppValue)++;
        (*pLength)--;

        // Prevent underflows.
        if (*pLength == 0)
        {
            return;
        }
    }

    ABC_LOG("Length after prefix strip: %zu", *pLength);

    ABC_LOG("About to check char %zu: (0x%x) `%c`",
            *pLength - 1, (*ppValue)[*pLength - 1], (*ppValue)[*pLength - 1]);

    // Ignore trailing white space.
    while ((*ppValue)[*pLength - 1] == ' '  ||
           (*ppValue)[*pLength - 1] == '\n' ||
           (*ppValue)[*pLength - 1] == '\t')
    {
        ABC_LOG("Removing trailing char %zu: (0x%x) `%c`",
                *pLength - 1, (*ppValue)[*pLength - 1], (*ppValue)[*pLength - 1]);

        (*pLength)--;

        // Prevent underflows.
        if (*pLength == 0)
        {
            return;
        }
    }

    ABC_LOG("Length after suffix strip: %zu", *pLength);

    for (size_t i = 0; i < *pLength; ++i)
    {
        ABC_LOG("Final string char %zu: `%c`", i, (*ppValue)[i]);
    }
}

static bool
extractKeyValue(
        const char *const pEntryStr,
        const char **const ppKeyStr,
        size_t *const restrict pKeyLen,
        int *const restrict pKeyVal)
{
    assert(pEntryStr && pKeyLen && pKeyVal);
    assert(strnlen(pEntryStr, ENTRY_MAX_LEN) < ENTRY_MAX_LEN);

    ABC_LOG("entry `%s`", pEntryStr);

    // Entry may look like this:
    // `sampling_period = 5 # Comment`

    // Detect the 3 components of an entry: key, value, comment.
    const char *pKeySubStr = pEntryStr;
    const char *pCommentSubStr = strchr(pEntryStr, '#');
    const char *pValueSubStr = strchr(pEntryStr, '=');

    // Validate the components.
    if (NULL == pValueSubStr)
    {
        ABC_LOG_ERR("No value present");

        return false;
    }

    if (pCommentSubStr)
    {
        if (pValueSubStr > pCommentSubStr)
        {
            ABC_LOG_ERR("Value inside comment");

            return false;
        }
    }

    // Calculate the lengths of each component.
    const size_t entryLen = strlen(pEntryStr);
    const size_t commentLen = pCommentSubStr ? strlen(pCommentSubStr) : 0;
    size_t keyLen = entryLen - strlen(pValueSubStr);
    size_t valueLen = entryLen - commentLen - keyLen - 1; // `-1` to exclude `=`.

    pValueSubStr++; // Skip `=`.

    ABC_LOG("Component lengths are %zu, %zu, %zu", keyLen, valueLen, commentLen);

    // Clean up the components.
    stripPrefixSuffixWhitespace(&pKeySubStr, &keyLen);
    stripPrefixSuffixWhitespace(&pValueSubStr, &valueLen);

    if (keyLen <= 0 || valueLen <= 0)
    {
        ABC_LOG_ERR("Bad key or value lengths (%zu and %zu)", keyLen, valueLen);

        return false;
    }

    ABC_LOG("Clean component lengths are %zu, %zu, %zu",
            keyLen, valueLen, commentLen);

    // Convert the value to int.
    char valueStr[valueLen + 1];
    int value;
    memcpy(valueStr, pValueSubStr, valueLen);
    valueStr[valueLen] = '\0';

    if (!abc_utils_strToInt(&value, valueStr))
    {
        ABC_LOG_ERR("Failed to convert value `%s` to int", valueStr);

        return false;
    }

    // Set output.
    *pKeyVal = value;
    *pKeyLen = keyLen;

    if (ppKeyStr)
    {
        *ppKeyStr = pKeySubStr;
    }

    ABC_LOG("Key value `%s` is %d", valueStr, value);

    return true;
}

static bool extractEntry(
        char *const restrict pEntry,
        const unsigned maxEntryBufLen,
        const abc_Key_t key,
        const char *const restrict pFileName)
{
    // Prepare grep commands.
    char grepCommand[1024 + 1];
    grepCommand[0] = '\0';
    strncat(grepCommand, "egrep \"^", sizeof(grepCommand) - 1);
    strncat(grepCommand, keyToStr(key), sizeof(grepCommand) - 1);
    strncat(grepCommand, "[ =\\t]\" ", sizeof(grepCommand) - 1);
    strncat(grepCommand, pFileName, sizeof(grepCommand) - 1);

    if (strlen(grepCommand) == sizeof(grepCommand) - 1)
    {
        ABC_LOG_ERR("Grep command too long");

        return false;
    }

    const bool cmdOK =
        abc_terminalController_sendReturnStr(
                maxEntryBufLen,
                pEntry,
                grepCommand);

    if (!cmdOK)
    {
        ABC_LOG_ERR("Failed to read entry");

        return false;
    }


    return true;
}

static bool
countEntries(
        int *const restrict pEntryCount,
        const abc_Key_t key,
        const char *const restrict pFileName)
{
    // Prepare sub-commands.
    char grepCommand[1024 + 1];
    grepCommand[0] = '\0';
    strncat(grepCommand, "egrep \"^", sizeof(grepCommand) - 1);
    strncat(grepCommand, keyToStr(key), sizeof(grepCommand) - 1);
    strncat(grepCommand, "[ =\\t]\" ", sizeof(grepCommand) - 1);
    strncat(grepCommand, pFileName, sizeof(grepCommand) - 1);

    if (strlen(grepCommand) == sizeof(grepCommand) - 1)
    {
        ABC_LOG_ERR("Grep command too long");
        return false;
    }

    const char wcCommand[] = "wc -l";
    const char pipe[] = " | ";

    // Build final command.
    char finalCommand[1024 + 1];
    finalCommand[0] = '\0';
    strncat(finalCommand, grepCommand, sizeof(finalCommand) - 1);
    strncat(finalCommand, pipe, sizeof(finalCommand) - 1);
    strncat(finalCommand, wcCommand, sizeof(finalCommand) - 1);

    if (strlen(finalCommand) == sizeof(finalCommand) - 1)
    {
        ABC_LOG_ERR("Final command too long");
        return false;
    }

    // Execute the command to count the number of entries in the file.
    char entryCountStr[11] = {'\0'};

    const bool cmdOK =
        abc_terminalController_sendReturnStr(
                sizeof(entryCountStr),
                entryCountStr,
                finalCommand);

    if (!cmdOK)
    {
        ABC_LOG_ERR("Failed to count entries");

        return false;
    }

    if (entryCountStr[strlen(entryCountStr) - 1] == '\n')
    {
        entryCountStr[strlen(entryCountStr) - 1] = '\0';
    }

    if (!abc_utils_strToInt(pEntryCount, entryCountStr))
    {
        ABC_LOG_ERR("Failed to convert value `%s` to int", entryCountStr);

        return false;
    }

    ABC_LOG("Entry count for `%s` is %d", keyToStr(key), *pEntryCount);

    return true;
}

static bool
readKeyValue(
        const abc_Key_t key,
        int *const restrict pValue,
        const char *const restrict pFileName)
{
    assert(isKeyValid(key) && pValue && pFileName);

    ABC_LOG("Key `%s`, filename `%s`", keyToStr(key), pFileName);

    // Count entries.
    int keyCount;
    if (!countEntries(&keyCount, key, pFileName))
    {
        ABC_LOG_ERR("Failed to count entries from `%s`", pFileName);

        return false;
    }

    if (0 == keyCount)
    {
        ABC_LOG_ERR("No key entries found");

        return false;
    }

    if (keyCount != 1)
    {
        ABC_LOG_ERR("Found duplicate key entries");

        return false;
    }

    // Read entry.
    char entryStr[ENTRY_MAX_LEN + 1];
    if (!extractEntry(entryStr, sizeof(entryStr), key, pFileName))
    {
        ABC_LOG_ERR("Failed to extract entry");

        return false;
    }

    // Parse entry.
    size_t actualKeyLen;
    if (!extractKeyValue(entryStr, NULL, &actualKeyLen, pValue))
    {
        ABC_LOG_ERR("Failed to parse config entry");

        return false;
    }

    if (actualKeyLen != strlen(keyToStr(key)))
    {
        ABC_LOG_ERR("Something went wrong during parsing, the actual "
                "key length %zu is different from %zu",
                actualKeyLen, strlen(keyToStr(key)));

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

    if (!isKeyValid(key))
    {
        ABC_LOG_ERR("Bad key %d", key);

        return false;
    }

    ABC_LOG("reading key `%s`", keyToStr(key));

    // Try to read from the host file.
    const bool isHostValueRead = readKeyValue(key, pValue, ABC_CONFIG_FILENAME);

    // If reading from host file fails, try reading from the defaults file.
    if (!isHostValueRead)
    {
        if (!readKeyValue(key, pValue, ABC_CONFIG_DEFAULTS_FILENAME))
        {
            ABC_LOG_ERR("Can't read key %d", key);

            return false;
        }
    }

    ABC_LOG("Setting key `%s` to %d read from `%s` file",
            keyToStr(key), *pValue, isHostValueRead ? "host" : "defaults");

    return true;
}
