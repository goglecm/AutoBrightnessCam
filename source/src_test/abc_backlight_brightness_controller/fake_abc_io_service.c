#include "abc_io_service/abc_io_service.h"
#include "abc_backlight_brightness_controller/fake_abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static uint16_t
s_currentBrightness;

static bool
s_isCurrentBrightnessSet = false;

static unsigned
s_numWriteCalls;

static uint16_t
s_maxBrightness;

static bool
s_isMaxBrightnessSet = false;

static bool
s_isReadFailed = false;

bool
abc_ioService_write(const int value, const char *const restrict pFileName)
{
    if (NULL == pFileName)
    {
        return false;
    }

    ++s_numWriteCalls;

    s_currentBrightness = value;

    s_isCurrentBrightnessSet = true;

    return true;
}

bool
abc_ioService_read(int *const restrict pValue,
                   const char *const restrict pFileName)
{
    if (s_isReadFailed)
    {
        return false;
    }

    assert(pValue && pFileName);

    if (0 == strcmp(pFileName, "max_brightness"))
    {
        ABC_LOG_ERR("max brightness not set");

        assert(s_isMaxBrightnessSet);

        *pValue = s_maxBrightness;
    }

    return true;
}

uint16_t
fake_abc_ioService_getCurrentBrightness(void)
{
    if (!s_isCurrentBrightnessSet)
    {
        ABC_LOG_ERR("current brightness not set");

        assert(false);
    }

    return s_currentBrightness;
}

unsigned
fake_abc_ioService_getNumWrites(void)
{
    return s_numWriteCalls;
}

void
fake_abc_ioService_resetNumWriteCalls(void)
{
    s_numWriteCalls = 0;
}

void
fake_abc_ioService_setMaxBrightness(const uint16_t value)
{
    s_maxBrightness = value;

    s_isMaxBrightnessSet = true;
}

void
fake_abc_ioService_failReads(const bool isReadFail)
{
    s_isReadFailed = isReadFail;
}