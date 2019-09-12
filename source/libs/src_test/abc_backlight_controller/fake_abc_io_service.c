#include "abc_io_service/abc_io_service.h"
#include "abc_backlight_controller/fake_abc_io_service.h"

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
        ABC_LOG_WRN("bad filename");

        return false;
    }

    ABC_LOG("writing %d to %s", value, pFileName);

    ++s_numWriteCalls;

    s_currentBrightness = (uint16_t)value;

    s_isCurrentBrightnessSet = true;

    return true;
}

bool
abc_ioService_read(int *const restrict pValue,
                   const char *const restrict pFileName)
{
    if (s_isReadFailed)
    {
        ABC_LOG("set to fail reads");

        return false;
    }

    assert(pValue && pFileName);

    if (0 == strcmp(pFileName, "max_brightness"))
    {
        ABC_LOG("reading max brightness");

        if (s_isMaxBrightnessSet)
        {
            ABC_LOG("max brightness read is %u", s_maxBrightness);

            *pValue = s_maxBrightness;
        }
        else
        {
            ABC_LOG_ERR("max brightness not set");

            assert(false);
        }
    }
    else if (0 == strcmp(pFileName, "current_brightness"))
    {
        ABC_LOG("reading current brightness");

        if (s_isCurrentBrightnessSet)
        {
            ABC_LOG("current brightness is %u", s_currentBrightness);

            *pValue = s_currentBrightness;
        }
        else
        {
            ABC_LOG_ERR("current brightness not set");

            assert(false);
        }
    }
    else
    {
        ABC_LOG_ERR("reading unknown file");

        assert(false);

        return false;
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

    ABC_LOG("current brightness is %u", s_currentBrightness);

    return s_currentBrightness;
}

unsigned
fake_abc_ioService_getNumWrites(void)
{
    ABC_LOG("num calls = %u", s_numWriteCalls);

    return s_numWriteCalls;
}

void
fake_abc_ioService_resetNumWriteCalls(void)
{
    ABC_LOG("resetting number of write calls");

    s_numWriteCalls = 0;
}

void
fake_abc_ioService_setMaxBrightness(const uint16_t value)
{
    ABC_LOG("setting max brightness from %u to %u", s_maxBrightness, value);

    s_maxBrightness = value;

    s_isMaxBrightnessSet = true;
}

void
fake_abc_ioService_setCurrentBrightness(const uint16_t value)
{
    ABC_LOG("setting current brightness from %u to %u", s_currentBrightness, value);

    s_currentBrightness = value;

    s_isCurrentBrightnessSet = true;
}

void
fake_abc_ioService_failReads(const bool isReadFail)
{
    ABC_LOG("setting fail reads from %u to %u", s_isReadFailed, isReadFail);

    s_isReadFailed = isReadFail;
}
