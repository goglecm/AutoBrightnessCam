#include "abc_backlight_brightness_controller.h"

#include "abc_terminal_controller.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

const double g_abc_BacklightBrightnessController_MAX = 100;

const double g_abc_BacklightBrightnessController_MIN = 50;

static bool
s_isMaxSet = false;

static uint32_t
s_maxBrightness = -1;

static uint32_t readMaxBrightness(void)
{
    const char f[] = "/sys/class/backlight/intel_backlight/max_brightness";

    int maxBrightness;

    const bool result = abc_terminalController_readFile(&maxBrightness, f);

    assert(result);

    assert(maxBrightness > 0);

    return maxBrightness;
}

static void writeBrightness(const uint32_t value)
{
    const char f[] = "/sys/class/backlight/intel_backlight/brightness";

    const bool result = abc_terminalController_writeFile(value, f);

    assert(result);
}

void abc_backlightBrightnessController_set(const double value)
{
    if (false == s_isMaxSet)
    {
        s_maxBrightness = readMaxBrightness();
        s_isMaxSet = true;
    }

    writeBrightness((double) s_maxBrightness * (value / 100.0));
}
