#include <gtest/gtest.h>

#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"

#include "abc_terminal_controller/abc_terminal_controller.h"

#include "abc_backlight_brightness_controller/fake_abc_terminal_controller.h"

TEST(abc_backlight_brightness_controller, backlight_brightness_is_set_to_new_value)
{
    const uint16_t max = 6900;

    // Mid point between min and max
    const double target = (g_abc_BacklightBrightnessController_MAX -
                          g_abc_BacklightBrightnessController_MIN) / 2 +
                          g_abc_BacklightBrightnessController_MIN;

    fake_abc_terminalController_setMaxBrightness(max);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(max * (target / 100.0),
              fake_abc_terminalController_getCurrentBrightness());
}

TEST(abc_backlight_brightness_controller, backlight_brightness_does_not_exceed_maximum_brightness)
{
    const uint16_t max = 6900;

    const double target = g_abc_BacklightBrightnessController_MAX * 1.5;

    fake_abc_terminalController_setMaxBrightness(max);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ((g_abc_BacklightBrightnessController_MAX / 100.0) * max,
              fake_abc_terminalController_getCurrentBrightness());
}

TEST(abc_backlight_brightness_controller, backlight_brightness_does_not_recede_minimum_brightness)
{
    const uint16_t max = 6900;

    const double target = g_abc_BacklightBrightnessController_MIN / 2;

    fake_abc_terminalController_setMaxBrightness(max);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(g_abc_BacklightBrightnessController_MIN / 100 * max,
              fake_abc_terminalController_getCurrentBrightness());
}
