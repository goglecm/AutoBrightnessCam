#include <gtest/gtest.h>

#include "abc_brightness_calculator.h"

TEST(ABC_brightness_calculator, newBrightnessIsGreaterOrEqualThanTheMinimumBrightness)
{
    abc_Percentage_t newBrightness;

    newBrightness = abc_calculateNewBrightnessPercentage(g_abc_MIN_BRIGHTNESS - 1);

    ASSERT_GE(newBrightness, g_abc_MIN_BRIGHTNESS);

    newBrightness = abc_calculateNewBrightnessPercentage(2 * g_abc_MIN_BRIGHTNESS);

    ASSERT_GE(newBrightness, g_abc_MIN_BRIGHTNESS);
}

TEST(ABC_brightness_calculator, newBrightnessIsLessOrEqualThanTheMaximumBrightness)
{
    abc_Percentage_t newBrightness;

    newBrightness = abc_calculateNewBrightnessPercentage(g_abc_MAX_BRIGHTNESS / 2);

    ASSERT_LE(newBrightness, g_abc_MAX_BRIGHTNESS);

    newBrightness = abc_calculateNewBrightnessPercentage(g_abc_MAX_BRIGHTNESS);

    ASSERT_LE(newBrightness, g_abc_MAX_BRIGHTNESS);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
