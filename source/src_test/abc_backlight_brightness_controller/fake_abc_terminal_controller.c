#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_backlight_brightness_controller/fake_abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static uint16_t
s_currentBrightness;

static bool
s_isCurrentBrightnessSet = false;

static uint16_t
s_maxBrightness;

static bool
s_isMaxBrightnessSet = false;

static bool
s_isReadFailed = false;

static unsigned
s_numWriteCalls;

bool
abc_terminalController_writeFile(int value, const char *pFileName)
{
    if (NULL == pFileName)
    {
        return false;
    }

    s_currentBrightness = value;

    s_isCurrentBrightnessSet = true;

    return true;
}

bool
abc_terminalController_readFile(int *const restrict pValue,
                                const char *const restrict pFileName)
{
    if (!s_isMaxBrightnessSet)
    {
        ABC_LOG_ERR("max brightness has not been set");
        assert(false);
    }

    if (NULL == pValue || NULL == pFileName)
    {
        return false;
    }

    *pValue = s_maxBrightness;

    return s_isReadFailed;
}

void fake_abc_terminalController_setMaxBrightness(const uint16_t value)
{
    ABC_LOG("max brightness set to %u", value);

    s_maxBrightness = value;

    s_isMaxBrightnessSet = true;
}

uint16_t fake_abc_terminalController_getCurrentBrightness(void)
{
    if (!s_isCurrentBrightnessSet)
    {
        ABC_LOG_ERR("current brightness not set");

        assert(false);
    }

    return s_currentBrightness;
}

void
fake_abc_terminalController_failRead(const bool failReads)
{
    s_isReadFailed = !failReads;
}

unsigned
fake_abc_terminalController_getNumWrites(void)
{
    return s_numWriteCalls;
}

void
fake_abc_terminalController_resetNumWriteCalls(void)
{
    s_numWriteCalls = 0;
}
