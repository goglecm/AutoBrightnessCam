/****************
 * Main include *
 ****************/

#include "abc_brightness_calculator.h"

/******************************
 * Local function definitions *
 ******************************/

static abc_Percentage_t
limitToMaxBrightness(const abc_Percentage_t brightness)
{
    if (brightness > g_abc_MAX_BRIGHTNESS)
    {
        return g_abc_MAX_BRIGHTNESS;
    }

    return brightness;
}

static abc_Percentage_t
limitToMinBrightness(const abc_Percentage_t brightness)
{
    if (brightness < g_abc_MIN_BRIGHTNESS)
    {
        return g_abc_MIN_BRIGHTNESS;
    }

    return brightness;
}

/*******************************
 * Global variable definitions *
 *******************************/

const abc_Percentage_t g_abc_MIN_BRIGHTNESS = 5;
const abc_Percentage_t g_abc_MAX_BRIGHTNESS = 100;

/*******************************
 * Global function definitions *
 *******************************/

abc_Percentage_t
abc_calculateNewBrightness(abc_Percentage_t ambientBrightness)
{
    return limitToMinBrightness(limitToMaxBrightness(ambientBrightness));
}
