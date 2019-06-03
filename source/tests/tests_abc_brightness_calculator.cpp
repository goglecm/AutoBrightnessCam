#include <gtest/gtest.h>

#include "abc_brightness_calculator.h"

TEST(ABC_brightness_calculator, calculatedBrightnessIsGreaterOrEqualThanTheMinimumBrightness)
{
    abc_Percentage_t newBrightness, ambientBrightness;

    ambientBrightness = g_abc_MIN_BRIGHTNESS - 1;
    newBrightness = abc_calculateNewBrightness(ambientBrightness);

    ASSERT_GE(newBrightness, g_abc_MIN_BRIGHTNESS);

    ambientBrightness = 2 * g_abc_MIN_BRIGHTNESS;
    newBrightness = abc_calculateNewBrightness(ambientBrightness);

    ASSERT_GE(newBrightness, g_abc_MIN_BRIGHTNESS);
}

TEST(ABC_brightness_calculator, calculatedBrightnessIsLessOrEqualThanTheMaximumBrightness)
{
    abc_Percentage_t newBrightness, ambientBrightness;

    ambientBrightness = g_abc_MAX_BRIGHTNESS / 2;
    newBrightness = abc_calculateNewBrightness(ambientBrightness);

    ASSERT_LE(newBrightness, g_abc_MAX_BRIGHTNESS);

    ambientBrightness = g_abc_MAX_BRIGHTNESS;
    newBrightness = abc_calculateNewBrightness(ambientBrightness);

    ASSERT_LE(newBrightness, g_abc_MAX_BRIGHTNESS);
}

TEST(ABC_brightness_calculator, calculatedBrightnessIsTheSameAsAmbientBrightness)
{
    const abc_Percentage_t ambientBrightness = 70;

    ASSERT_EQ(abc_calculateNewBrightness(ambientBrightness), ambientBrightness);
}
