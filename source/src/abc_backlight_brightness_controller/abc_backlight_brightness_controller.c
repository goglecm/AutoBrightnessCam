#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"
#include "abc_terminal_controller/abc_terminal_controller.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

const double
g_abc_BacklightBrightnessController_MAX = 100;

const double
g_abc_BacklightBrightnessController_MIN = 50;

static bool
s_isMaxSet = false;

static uint32_t
s_maxBrightness = -1;

static const char
s_PATH_MAX_BRIGHTNESS[] = "/sys/class/backlight/intel_backlight/max_brightness";

static const char
s_PATH_CURRENT_BRIGHTNESS[] = "/sys/class/backlight/intel_backlight/brightness";

static uint32_t
readMaxBrightness(void)
{
    int maxBrightness;

    const bool result =
        abc_terminalController_readFile(&maxBrightness, s_PATH_MAX_BRIGHTNESS);

    assert(result);

    assert(maxBrightness > 0);

    return maxBrightness;
}

static void
writeBrightness(const uint32_t value)
{
    const bool result =
        abc_terminalController_writeFile(value, s_PATH_CURRENT_BRIGHTNESS);

    assert(result);
}

static double
limitBrightness(const double value)
{
    if (value > g_abc_BacklightBrightnessController_MAX)
    {
        return g_abc_BacklightBrightnessController_MAX;
    }
    else if (value < g_abc_BacklightBrightnessController_MIN)
    {
        return g_abc_BacklightBrightnessController_MIN;
    }
    else
    {
        return value;
    }
}

void
abc_backlightBrightnessController_set(const double value)
{
    if (false == s_isMaxSet)
    {
        s_maxBrightness = readMaxBrightness();
        s_isMaxSet = true;
    }

    writeBrightness(s_maxBrightness * (limitBrightness(value) / 100.0));
}
