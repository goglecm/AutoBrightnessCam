#include <gtest/gtest.h>

#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"

#include "abc_io_service/abc_io_service.h"

#include "abc_backlight_brightness_controller/fake_abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include <fstream>

static const uint16_t
s_DEFAULT_MAX = 6900;

static const char s_CURRENT_BRIGHTNESS_PATH[] = "current_brightness";

static const char s_MAX_BRIGHTNESS_PATH[] = "max_brightness";

static double
getMidBrightness(void)
{
    return (g_abc_BacklightBrightnessController_MAX -
            g_abc_BacklightBrightnessController_MIN) / 2 +
           g_abc_BacklightBrightnessController_MIN;
}

static uint16_t
toRawBrightness(const double target)
{
    return target / 100.0 * s_DEFAULT_MAX;
}

class abc_backlight_brightness_controller: public ::testing::Test
{

public:
    abc_backlight_brightness_controller(void)
    {
        // initialization code here
    }

    void SetUp(void)
    {
        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());

        // code here will execute just before the test ensues

        abc_backlightBrightnessController_setCurrentPath(s_CURRENT_BRIGHTNESS_PATH);
        abc_backlightBrightnessController_setMaxPath(s_MAX_BRIGHTNESS_PATH);

        abc_backlightBrightnessController_resetMax();

        fake_abc_ioService_resetNumWriteCalls();

        fake_abc_ioService_setMaxBrightness(s_DEFAULT_MAX);

        fake_abc_ioService_failReads(false);
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
    const double target = getMidBrightness();

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(target),
              fake_abc_ioService_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, backlight_brightness_does_not_exceed_maximum_brightness)
{
    const double target = g_abc_BacklightBrightnessController_MAX * 1.5;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(g_abc_BacklightBrightnessController_MAX),
              fake_abc_ioService_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, backlight_brightness_does_not_recede_minimum_brightness)
{
    const double target = g_abc_BacklightBrightnessController_MIN / 2;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(g_abc_BacklightBrightnessController_MIN),
              fake_abc_ioService_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_the_maximum_brightness_is_zero)
{
    // Mid point between min and max
    const double target = getMidBrightness();

    fake_abc_ioService_setMaxBrightness(0);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_ioService_getNumWrites());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_maximum_brightness_cannot_be_read)
{
    // Mid point between min and max
    const double target = getMidBrightness();

    fake_abc_ioService_failReads(true);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_ioService_getNumWrites());
}
