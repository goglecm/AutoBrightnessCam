#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"
#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_BUFF_SIZE 128U

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

static bool
readIntFromFile(int *const restrict pValue,
                const char *const restrict pFileName)
{
    if (NULL == pFileName)
    {
        ABC_LOG_ERR("Invalid filename");

        return false;
    }

    char cmd[MAX_BUFF_SIZE] = { 0 };

    int result;
    result = snprintf(cmd, sizeof(cmd), "cat %s", pFileName);

    if (result <= 0)
    {
        ABC_LOG_ERR("Returning false: Failed to construct the cmd to read the file");

        return false;
    }

    char strValue[MAX_BUFF_SIZE] = { 0 };

    if (!abc_terminalController_sendReturnStr(sizeof(strValue), strValue, cmd))
    {
        return false;
    }

    if (pValue)
    {
        *pValue = strtoimax(strValue, NULL, 10);

        ABC_LOG("return value = %d", *pValue);
    }

    return true;
}


// return true on success
static bool
readMaxBrightness(uint32_t *const restrict pRetValue)
{
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

    if (pRetValue)
    {
        *pRetValue = maxBrightness;
    }
    else
    {
        ABC_LOG_WRN("invalid result pointer, not returning the max brightness");
    }

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
