#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"
#include "abc_terminal_controller/abc_terminal_controller.h"
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

static bool
strToInt(int *const restrict pValue, const char *const restrict pStr)
{
    assert(pValue && pStr);

    char *pEnd;
    const long readNum = strtol(pStr, &pEnd, 10);
    if (errno)
    {
        ABC_LOG_ERR("Failed to convert string to long due to: %s", strerror(errno));

        return false;
    }

    // Check if anything was read.
    if (pEnd == pStr)
    {
        ABC_LOG_ERR("Failed to convert string to long as nothing was read");

        return false;
    }

    // A full conversion occurs when pEnd is null or '\n'.
    if (*pEnd && *pEnd != '\n')
    {
        ABC_LOG_ERR("Failed to convert the string fully to long");

        return false;
    }

    if (readNum > INT_MAX || readNum < INT_MIN)
    {
        ABC_LOG_ERR("The read value (%lu) is too large", readNum);

        return false;
    }

    *pValue = readNum;

    return true;
}

static bool
readIntFromFile(int *const restrict pValue,
                const char *const restrict pFileName)
{
    if (NULL == pFileName || NULL == pValue)
    {
        ABC_LOG_ERR("Bad filename = %p or bad ret value = %p",
                    (void *)pFileName, (void *)pValue);

        assert(false);

        return false;
    }

    FILE *const pFile = fopen(pFileName, "r");

    if (NULL == pFile)
    {
        ABC_LOG_ERR("Failed to open the file due to: %s", strerror(errno));

        return false;
    }

    bool isReturnOK = true;

    char readLine[10] = { 0 };

    if (NULL == fgets(readLine, sizeof(readLine), pFile))
    {
        ABC_LOG_ERR("Reached EOF too early");

        isReturnOK = false;
    }
    else if (errno)
    {
        ABC_LOG_ERR("Failed to read the file due to: %s", strerror(errno));

        isReturnOK = false;
    }
    else
    {
        ABC_LOG("Read `%s` from file %s", readLine, pFileName);
    }

    fclose(pFile);

    if (!isReturnOK)
    {
        return false;
    }

    if (!strToInt(pValue, readLine))
    {
        ABC_LOG_ERR("Failed to read convert string to int");

        return false;
    }

    return true;
}

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

    if (!readIntFromFile(&maxBrightness, s_PATH_MAX_BRIGHTNESS))
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
    if (!abc_terminalController_writeFile(value, s_PATH_CURRENT_BRIGHTNESS))
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
