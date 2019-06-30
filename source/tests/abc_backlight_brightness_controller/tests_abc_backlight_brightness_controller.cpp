#include <gtest/gtest.h>

#include "abc_backlight_brightness_controller.h"

#include "abc_terminal_controller.h"

#include "abc_backlight_brightness_controller/fake_abc_terminal_controller.h"

TEST(abc_backlight_brightness_controller, backlight_brightness_is_set_to_new_value)
{
    const uint16_t max = 6900;

    const double target = 45.0;

    fake_abc_terminalController_setMaxBrightness(max);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(max * (target / 100.0),
              fake_abc_terminalController_getCurrentBrightness());
}
