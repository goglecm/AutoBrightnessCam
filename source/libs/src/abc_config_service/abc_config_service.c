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


#define ENTRY_MAX_LEN 256


typedef abc_configService_Key_t abc_Key_t;


// Updating length and pointer to point to the value without whitespace around.
static void
stripPrefixSuffixWhitespace(const char **const ppValue, size_t *const pLength)
{
    assert(ppValue && *ppValue && pLength);

    ABC_LOG("starting length %zu", *pLength);

    if (*pLength == 0)
    {
        return;
    }

    // Skip prefixed whitespace from the value.
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

    // Ignore trailing whitespace.
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

static inline bool
isKeyValid(const abc_Key_t key)
{
    return key == ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD ||
           key == ABC_CONFIG_SERVICE_KEY_TRANSITION_SMOOTHNESS;
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

        default:
            assert(false && "Bad key");
            return NULL;
    }
}

static bool
readKeyValue(
        const abc_Key_t key,
        int *const restrict pValue,
        const char *const restrict pFileName)
{
    assert(isKeyValid(key) && pValue && pFileName);

    ABC_LOG("Key `%s`, filename `%s`", keyToStr(key), pFileName);

    char entryStr[ENTRY_MAX_LEN + 1];

    const char *pOrigKeyStr = keyToStr(key);
    const size_t origKeyLen = strlen(pOrigKeyStr);

    // Read corresponding entry from the file. Try a couple of terminators for
    // the key string.
    char keyStr[origKeyLen + 2];
    memcpy(keyStr, pOrigKeyStr, origKeyLen + 1);
    keyStr[origKeyLen + 1] = '\0';

    const char keyTerminatorChars[] = {' ', '=', '\0'};
    bool isEntryRead;
    for (size_t i = 0; i < sizeof(keyTerminatorChars); ++i)
    {
        keyStr[origKeyLen] = keyTerminatorChars[i];

        ABC_LOG("Attempt to read with starting str `%s`", keyStr);

        isEntryRead =
            abc_ioService_readLineStartingWith(
                    keyStr,
                    entryStr,
                    sizeof(entryStr),
                    pFileName);

        if (isEntryRead)
        {
            break;
        }
    }

    // Extract the value from the entry.
    if (isEntryRead)
    {
        size_t actualKeyLen;
        if (!extractKeyValue(entryStr, NULL, &actualKeyLen, pValue))
        {
            ABC_LOG_ERR("Failed to parse config entry");

            return false;
        }

        if (actualKeyLen != strlen(keyToStr(key)))
        {
            ABC_LOG_ERR("Key not present in file");

            return false;
        }
    }
    else
    {
        ABC_LOG("Failed to read config entry");

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
