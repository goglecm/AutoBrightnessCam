#include "abc_io_service/abc_io_service.h"
#include "abc_logging_service/abc_logging_service.h"

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

const double
g_abc_BacklightBrightnessController_MAX = 100;

const double
g_abc_BacklightBrightnessController_MIN = 50;

static bool
s_isMaxSet = false;

static uint32_t
s_maxBrightness = -1;

static char
s_PATH_MAX_BRIGHTNESS[MAX_BUFF_SIZE];

static char
s_PATH_CURRENT_BRIGHTNESS[MAX_BUFF_SIZE];

// return true on success
static bool
readMaxBrightness(uint32_t *const restrict pRetValue)
{
    if (NULL == pRetValue)
    {
        ABC_LOG_ERR("Invalid result pointer, not returning the max brightness");

        assert(false);

        return false;
    }

    int maxBrightness = 0;

    if (!abc_ioService_read(&maxBrightness, s_PATH_MAX_BRIGHTNESS))
    {
        ABC_LOG_ERR("Failed to read max brightness");

        return false;
    }

    if (0 == maxBrightness)
    {
        ABC_LOG_ERR("max brightness is zero");

        return false;
    }

    *pRetValue = maxBrightness;

    ABC_LOG("max brightness = %u", *pRetValue);

    return true;
}

static void
writeBrightness(const uint32_t value)
{
    if (!abc_ioService_write(value, s_PATH_CURRENT_BRIGHTNESS))
    {
        ABC_LOG_ERR("failed to set the brightness to %u", value);
    }
}

static double
limitBrightness(const double value)
{
    if (value > g_abc_BacklightBrightnessController_MAX)
    {
        ABC_LOG("returning %f", g_abc_BacklightBrightnessController_MAX);

        return g_abc_BacklightBrightnessController_MAX;
    }
    else if (value < g_abc_BacklightBrightnessController_MIN)
    {
        ABC_LOG("returning %f", g_abc_BacklightBrightnessController_MIN);

        return g_abc_BacklightBrightnessController_MIN;
    }
    else
    {
        ABC_LOG("returning %f", value);

        return value;
    }
}

static bool
arePathsSet(void)
{
    return !(s_PATH_MAX_BRIGHTNESS[0] == 0 || s_PATH_CURRENT_BRIGHTNESS[0] == 0);
}

static void
setDefaultPaths(void)
{
    const char defaultMaxPath[] = "/sys/class/backlight/intel_backlight/max_brightness";
    const char defaultCurrentPath[] = "/sys/class/backlight/intel_backlight/brightness";
    memcpy(s_PATH_MAX_BRIGHTNESS, defaultMaxPath,
           strnlen(defaultMaxPath, sizeof(s_PATH_MAX_BRIGHTNESS) - 1) + 1);

    memcpy(s_PATH_CURRENT_BRIGHTNESS, defaultCurrentPath,
           strnlen(defaultCurrentPath, sizeof(s_PATH_CURRENT_BRIGHTNESS) - 1) + 1);
}

void
abc_backlightBrightnessController_set(const double value)
{
    if (!arePathsSet())
    {
        setDefaultPaths();
    }

    if (!s_isMaxSet)
    {
        if (!readMaxBrightness(&s_maxBrightness))
        {
            ABC_LOG_ERR("failed to read max brightness, returning");

            return;
        }

        s_isMaxSet = true;
    }

    writeBrightness(s_maxBrightness * (limitBrightness(value) / 100.0));
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
    if (pPath)
    {
        memcpy(s_PATH_MAX_BRIGHTNESS, pPath,
               strnlen(pPath, sizeof(s_PATH_MAX_BRIGHTNESS) - 1) + 1);
    }
    else
    {
        ABC_LOG_ERR("bad max path, path remains unchanged");

        assert(false);
    }
}

// Function to set the path where the current brightness can be set/read.
void
abc_backlightBrightnessController_setCurrentPath(const char *const restrict pPath)
{
    if (pPath)
    {
        memcpy(s_PATH_CURRENT_BRIGHTNESS, pPath,
               strnlen(pPath, sizeof(s_PATH_CURRENT_BRIGHTNESS) - 1) + 1);
    }
    else
    {
        ABC_LOG_ERR("bad current path, path remains unchanged");

        assert(false);
    }
}
