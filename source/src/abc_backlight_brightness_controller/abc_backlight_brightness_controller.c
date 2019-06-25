#include "abc_backlight_brightness_controller.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

const double g_abc_BacklightBrightnessController_MAX = 100;

const double g_abc_BacklightBrightnessController_MIN = 10;

static bool
s_isMaxSet = false;

static uint32_t
s_maxBrightness = -1;

void abc_backlightBrightnessController_set(const double value)
{
    if (false == s_isMaxSet)
    {
        const char cmd[] = "cat /sys/class/backlight/intel_backlight/max_brightness";

        FILE *const pProcessOut_file = popen(cmd, "r");

        assert(pProcessOut_file);

        char rawValueMax[10] = { 0 };
        if (NULL == fgets(rawValueMax, sizeof(rawValueMax), pProcessOut_file))
        {
            assert(false);
        }

        if (pclose(pProcessOut_file))
        {
            assert(false);
        }

        s_maxBrightness = strtoimax(rawValueMax, NULL, 10);

        assert(s_maxBrightness);

        s_isMaxSet = true;
    }

    {
        const uint32_t newBrightness = (uint32_t) ((double) s_maxBrightness * (value / 100));

        char cmd[128] = { 0 };

        if (snprintf(cmd, sizeof(cmd), "echo %"PRIu32" > /sys/class/backlight/intel_backlight/brightness", newBrightness) < 0)
        {
            assert(false);
        }

        const int result = system(cmd);

        if (result)
        {
            printf("in value = %f, final = %u, max = %u, result = %d from cmd = %s\n", value, newBrightness, s_maxBrightness, result, cmd);

            assert(false);
        }
    }
}