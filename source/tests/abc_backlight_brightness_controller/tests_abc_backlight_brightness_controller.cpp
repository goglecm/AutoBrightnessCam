#include <gtest/gtest.h>

#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"

#include "abc_terminal_controller/abc_terminal_controller.h"

#include "abc_backlight_brightness_controller/fake_abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

static const uint16_t
s_DEFAULT_MAX = 6900;

class abc_backlight_brightness_controller: public ::testing::Test
{

public:
    abc_backlight_brightness_controller(void)
    {
        // initialization code here
    }

    void SetUp(void)
    {
        abc_backlightBrightnessController_resetMax();

        // code here will execute just before the test ensues
        fake_abc_terminalController_failRead(false);

        fake_abc_terminalController_setMaxBrightness(s_DEFAULT_MAX);

        fake_abc_terminalController_resetNumWriteCalls();
    }

    void TearDown(void)
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~abc_backlight_brightness_controller(void)
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
};

TEST_F(abc_backlight_brightness_controller, backlight_brightness_is_set_to_new_value)
{
    // Mid point between min and max
    const double target = (g_abc_BacklightBrightnessController_MAX -
                          g_abc_BacklightBrightnessController_MIN) / 2 +
                          g_abc_BacklightBrightnessController_MIN;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(s_DEFAULT_MAX * (target / 100.0),
              fake_abc_terminalController_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, backlight_brightness_does_not_exceed_maximum_brightness)
{
    const double target = g_abc_BacklightBrightnessController_MAX * 1.5;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ((g_abc_BacklightBrightnessController_MAX / 100.0) * s_DEFAULT_MAX,
              fake_abc_terminalController_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, backlight_brightness_does_not_recede_minimum_brightness)
{
    const double target = g_abc_BacklightBrightnessController_MIN / 2;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(g_abc_BacklightBrightnessController_MIN / 100 * s_DEFAULT_MAX,
              fake_abc_terminalController_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_the_maximum_brightness_cannot_be_retireved)
{
    const double target = g_abc_BacklightBrightnessController_MIN / 2;

    fake_abc_terminalController_failRead(true);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_terminalController_getNumWrites());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_the_maximum_brightness_is_zero)
{
    // Mid point between min and max
    const double target = (g_abc_BacklightBrightnessController_MAX -
                           g_abc_BacklightBrightnessController_MIN) / 2 +
                          g_abc_BacklightBrightnessController_MIN;

    fake_abc_terminalController_setMaxBrightness(0);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_terminalController_getNumWrites());
}
