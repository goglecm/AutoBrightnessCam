#include "abc_io_service/abc_io_service.h"
#include "abc_config_service/fake_abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include <string.h>
#include <assert.h>

static bool
s_configEntrySet = false;

static char
s_configEntry[512];

static bool
s_defaultConfigEntrySet = false;

static char
s_defaultConfigEntry[512];

void
fake_abc_ioService_setConfigEntry(const char *const restrict pEntryStr)
{
    assert(pEntryStr && strnlen(pEntryStr, 512) < 512);

    strcpy(s_configEntry, pEntryStr);

    s_configEntrySet = true;

    ABC_LOG("Set config entry to %s", s_configEntry);
}

void
fake_abc_ioService_setDefaultConfigEntry(const char *const restrict pEntryStr)
{
    assert(pEntryStr && strnlen(pEntryStr, 512) < 512);

    strcpy(s_defaultConfigEntry, pEntryStr);

    s_defaultConfigEntrySet = true;

    ABC_LOG("Set default config entry to %s", s_defaultConfigEntry);
}

bool
abc_ioService_readLineStartingWith(
        const char *const restrict pStartStr,
        char *const restrict pRetStr,
        const int retStrBufMaxLen,
        const char *const restrict pFileName)
{
    assert(pStartStr &&
           pRetStr &&
           pFileName &&
           strnlen(pFileName, 512) < 512 &&
           strnlen(pStartStr, 512) < 512);

    if (0 == strcmp(pFileName, ABC_CONFIG_FILENAME))
    {
        assert(s_configEntrySet);
        assert(retStrBufMaxLen > (int)strlen(s_configEntry));
        assert(strlen(pStartStr) <= strlen(s_configEntry));

        strcpy(pRetStr, s_configEntry);

        ABC_LOG("Returned config entry (set %d): %s",
                s_configEntrySet, s_configEntry);
    }
    else if (0 == strcmp(pFileName, ABC_CONFIG_DEFAULTS_FILENAME))
    {
        assert(s_defaultConfigEntrySet);
        assert(retStrBufMaxLen > (int)strlen(s_defaultConfigEntry));
        assert(strlen(pStartStr) <= strlen(s_defaultConfigEntry));

        strcpy(pRetStr, s_defaultConfigEntry);

        ABC_LOG("Returned default config entry (set %d): %s",
                s_defaultConfigEntrySet, s_defaultConfigEntry);
    }
    else
    {
        ABC_LOG_ERR("Bad filename `%s` for config", pFileName);

        assert(false);
    }

    return true;
}
