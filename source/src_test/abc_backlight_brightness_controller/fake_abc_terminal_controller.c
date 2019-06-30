#include "abc_terminal_controller.h"

#include "abc_backlight_brightness_controller/fake_abc_terminal_controller.h"

#include <assert.h>

#include <stddef.h>

static uint16_t
s_currentBrightness;

static bool
s_isCurrentBrightnessSet = false;

static uint16_t
s_maxBrightness;

static bool
s_isMaxBrightnessSet = false;

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
    assert(s_isMaxBrightnessSet);

    if (NULL == pValue || NULL == pFileName)
    {
        return false;
    }

    *pValue = s_maxBrightness;

    return true;
}

void fake_abc_terminalController_setMaxBrightness(const uint16_t value)
{
    s_maxBrightness = value;

    s_isMaxBrightnessSet = true;
}

uint16_t fake_abc_terminalController_getCurrentBrightness(void)
{
    assert(s_isCurrentBrightnessSet);

    return s_currentBrightness;
}
