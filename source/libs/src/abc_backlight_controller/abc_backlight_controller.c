#include "abc_backlight_controller/abc_backlight_controller.h"

#include "abc_io_service/abc_io_service.h"
#include "abc_logging_service/abc_logging_service.h"
#include "abc_time_service/abc_time_service.h"

#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_BUFF_SIZE 128U

#define MAX_NUM_INCREMENTS 20U

const double
g_abc_BacklightBrightnessController_MAX = 100;

const double
g_abc_BacklightBrightnessController_MIN = 5;

static bool
s_isMaxSet = false;

static char
s_PATH_MAX_BRIGHTNESS[MAX_BUFF_SIZE];

static char
s_PATH_CURRENT_BRIGHTNESS[MAX_BUFF_SIZE];


static int
s_numIncrements = MAX_NUM_INCREMENTS;

static unsigned
s_incrementPeriod_ms = 60;

static inline void
writeBrightness(const int value)
{
    if (!abc_ioService_write(value, s_PATH_CURRENT_BRIGHTNESS))
    {
        ABC_LOG_ERR("failed to set the brightness to %u", value);
    }
}

void
abc_backlightBrightnessController_set(const double value)
{
    // Make sure the paths are set (at least to their default values).
    const bool arePathsSet = s_PATH_MAX_BRIGHTNESS[0] && s_PATH_CURRENT_BRIGHTNESS[0];
    if (!arePathsSet)
    {
        abc_backlightBrightnessController_setMaxPath("/sys/class/backlight/intel_backlight/max_brightness");
        abc_backlightBrightnessController_setCurrentPath("/sys/class/backlight/intel_backlight/brightness");
    }

    // Make sure there is an up-to-date max brightness.
    static int s_maxBrightness = -1;
    if (!s_isMaxSet)
    {
        int maxBrightness;
        if (!abc_ioService_read(&maxBrightness, s_PATH_MAX_BRIGHTNESS))
        {
            ABC_LOG_ERR("Failed to read max brightness");

            return;
        }

        if (maxBrightness == 0)
        {
            ABC_LOG_ERR("bad max brightness");

            return;
        }

        s_maxBrightness = maxBrightness;

        s_isMaxSet = true;
    }

    int previousBrightness = 0;
    if (!abc_ioService_read(&previousBrightness, s_PATH_CURRENT_BRIGHTNESS))
    {
        ABC_LOG_ERR("Failed to read current brightness");

        return;
    }

    // Make sure the value is within the min/max limits.
    const double validValue =
        value > g_abc_BacklightBrightnessController_MAX ? g_abc_BacklightBrightnessController_MAX :
        value < g_abc_BacklightBrightnessController_MIN ? g_abc_BacklightBrightnessController_MIN :
        value;

    const int targetBrightness = (int)(s_maxBrightness * (validValue / 100));

    ABC_LOG("target = %d, previous = %d", targetBrightness, previousBrightness);

    if (targetBrightness == previousBrightness)
    {
        ABC_LOG("old brightness is the same as new, returning");

        return;
    }

    if (0 == s_incrementPeriod_ms)
    {
        ABC_LOG("period is 0, setting the new brightness in one go");

        writeBrightness(targetBrightness);

        return;
    }

    int prevIntermediateValue = previousBrightness;
    for (int incNum = 0; incNum < s_numIncrements; ++incNum)
    {
        const int intermediateValue =
            previousBrightness + ((targetBrightness - previousBrightness) * (incNum + 1)) / s_numIncrements;

        // Next increment is the same as the previous one, skip it.
        if (prevIntermediateValue == intermediateValue)
        {
            continue;
        }

        prevIntermediateValue = intermediateValue;

        ABC_LOG("intermediateValue = %d (%d of %d)",
                intermediateValue, incNum + 1, s_numIncrements);

        if (intermediateValue == 0)
        {
            ABC_LOG_ERR("bad intermediate value");

            assert(false);
        }

        writeBrightness(intermediateValue);

        abc_timeService_sleep_ms(s_incrementPeriod_ms);
    }
}

void
abc_backlightBrightnessController_resetMax(void)
{
    s_isMaxSet = false;
}

// Function to set the path where the max brightness can be read.
void
abc_backlightBrightnessController_setMaxPath(const char *const restrict pPath)
{
    if (NULL == pPath)
    {
        ABC_LOG_ERR("bad max path, path remains unchanged");

        assert(false);

        return;
    }

    memcpy(s_PATH_MAX_BRIGHTNESS, pPath,
           strnlen(pPath, sizeof(s_PATH_MAX_BRIGHTNESS) - 1) + 1);
}

// Function to set the path where the current brightness can be set/read.
void
abc_backlightBrightnessController_setCurrentPath(const char *const restrict pPath)
{
    if (NULL == pPath)
    {
        ABC_LOG_ERR("bad current path, path remains unchanged");

        assert(false);

        return;
    }

    memcpy(s_PATH_CURRENT_BRIGHTNESS, pPath,
           strnlen(pPath, sizeof(s_PATH_CURRENT_BRIGHTNESS) - 1) + 1);
}

bool
abc_backlightBrightnessController_setNumIncrements(const unsigned num)
{
    if (num == 0)
    {
        ABC_LOG_ERR("cannot set numIncrements to 0 or less");

        return false;
    }

    if (num > MAX_NUM_INCREMENTS)
    {
        ABC_LOG_ERR("numIncrements is too large %u", num);

        return false;
    }

    ABC_LOG("setting numIncrements to %d", num);

    s_numIncrements = (int)num;

    return true;
}

void
abc_backlightBrightnessController_setIncrementsPeriod_ms(const unsigned period_ms)
{
    ABC_LOG("setting period to %u", period_ms);

    s_incrementPeriod_ms = period_ms;
}
