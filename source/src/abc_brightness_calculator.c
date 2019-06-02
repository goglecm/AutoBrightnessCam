/****************
 * Main include *
 ****************/

#include "abc_brightness_calculator.h"

/*******************************
 * Global variable definitions *
 *******************************/

const abc_Percentage_t g_abc_MIN_BRIGHTNESS = 5;
const abc_Percentage_t g_abc_MAX_BRIGHTNESS = 100;

/*******************************
 * Global function definitions *
 *******************************/

abc_Percentage_t
abc_calculateNewBrightnessPercentage(const abc_Percentage_t ambientBrightness)
{
    // Offset the brightness to prevent setting a brightness below the minimum
    // allowed brightness.
    abc_Percentage_t newBrightness = ambientBrightness + g_abc_MIN_BRIGHTNESS;

    // Clip the new brightness at the maximum allowed brightness.
    if (newBrightness > g_abc_MAX_BRIGHTNESS)
    {
        newBrightness = g_abc_MAX_BRIGHTNESS;
    }

    return newBrightness;
}
