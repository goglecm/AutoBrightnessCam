#include <gtest/gtest.h>

#include "abc_backlight_controller/abc_backlight_controller.h"

#include "abc_io_service/abc_io_service.h"

#include "abc_backlight_controller/fake_abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include "testlib_io.h"

#include <fstream>

static const uint16_t
s_DEFAULT_RAW_MAX = 6900;

static const char s_CURRENT_BRIGHTNESS_PATH[] = "current_brightness";

static const char s_MAX_BRIGHTNESS_PATH[] = "max_brightness";

static double
getMidBrightness(void)
{
    return (abc_backlightBrightnessController_getMax() -
            abc_backlightBrightnessController_getMin()) / 2 +
           abc_backlightBrightnessController_getMin();
}

static uint16_t
toRawBrightness(const double target)
{
    return target / 100.0 * s_DEFAULT_RAW_MAX;
}

class abc_backlight_controller: public ::testing::Test
{
public:
    void SetUp(void)
    {
        ASSERT_TRUE(abc_loggingService_setLogName(SPECIFIC_LOG_NAME));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());

        // code here will execute just before the test ensues

        abc_backlightBrightnessController_setCurrentPath(s_CURRENT_BRIGHTNESS_PATH);
        abc_backlightBrightnessController_setMaxPath(s_MAX_BRIGHTNESS_PATH);

        abc_backlightBrightnessController_resetMax();

        fake_abc_ioService_resetNumWriteCalls();

        fake_abc_ioService_setMaxBrightness(s_DEFAULT_RAW_MAX);

        fake_abc_ioService_failReads(false);

        ASSERT_TRUE(abc_backlightBrightnessController_setNumIncrements(10));

        abc_backlightBrightnessController_setIncrementsPeriod_ms(50);

        fake_abc_ioService_setCurrentBrightness((getMidBrightness() / 100) * (double)s_DEFAULT_RAW_MAX - 1);

        ASSERT_TRUE(abc_backlightBrightnessController_setMinMax(5, 95));
    }
};

TEST_F(abc_backlight_controller, backlight_is_set_to_new_value)
{
    // Mid point between min and max
    const double target = getMidBrightness();

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(target),
              fake_abc_ioService_getCurrentBrightness());
}

TEST_F(abc_backlight_controller, fail_to_set_max_brightness_over_min_brightness)
{
    ASSERT_FALSE(abc_backlightBrightnessController_setMinMax(50, 40));
}

TEST_F(abc_backlight_controller, set_valid_min_max_brightness)
{
    ASSERT_TRUE(abc_backlightBrightnessController_setMinMax(10, 40));
}

TEST_F(abc_backlight_controller, fail_to_set_out_of_range_min_max_brightness)
{
    ASSERT_FALSE(abc_backlightBrightnessController_setMinMax(-1, 40));
    ASSERT_FALSE(abc_backlightBrightnessController_setMinMax(0, 140));
}

TEST_F(abc_backlight_controller, backlight_is_updated_gradually)
{
    abc_backlightBrightnessController_setNumIncrements(3);
    abc_backlightBrightnessController_setIncrementsPeriod_ms(300);

    const double currentBrightness = (fake_abc_ioService_getCurrentBrightness() * 100.0) / s_DEFAULT_RAW_MAX;

    // Setting the target to be the mid-point between the current and max.
    const double targetBrightness =
        (abc_backlightBrightnessController_getMax() + currentBrightness) / 2;

    abc_backlightBrightnessController_set(targetBrightness);

    // Expecting 3 increments as we've set the number of increments to 3.
    ASSERT_EQ(3, fake_abc_ioService_getNumWrites());
}

TEST_F(abc_backlight_controller, only_unique_intermediate_brightness_updates_are_applied)
{
    abc_backlightBrightnessController_setNumIncrements(3);
    abc_backlightBrightnessController_setIncrementsPeriod_ms(300);

    const double targetBrightness = ((fake_abc_ioService_getCurrentBrightness() + 1) * 100.0) / s_DEFAULT_RAW_MAX;

    abc_backlightBrightnessController_set(targetBrightness);

    // The difference between the current and target is 1, but the number of
    // increments is 3 of which only 1 is applied.
    ASSERT_EQ(1, fake_abc_ioService_getNumWrites());
}

TEST_F(abc_backlight_controller, backlight_does_not_exceed_maximum_brightness)
{
    const double target = abc_backlightBrightnessController_getMax() * 1.5;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(abc_backlightBrightnessController_getMax()),
              fake_abc_ioService_getCurrentBrightness());
}

TEST_F(abc_backlight_controller, backlight_does_not_recede_minimum_brightness)
{
    const double target = abc_backlightBrightnessController_getMin() / 2;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(abc_backlightBrightnessController_getMin()),
              fake_abc_ioService_getCurrentBrightness());
}

TEST_F(abc_backlight_controller, brightness_is_not_set_when_the_maximum_brightness_is_zero)
{
    // Mid point between min and max
    const double target = getMidBrightness();

    fake_abc_ioService_setMaxBrightness(0);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_ioService_getNumWrites());
}

TEST_F(abc_backlight_controller, brightness_is_not_set_when_maximum_brightness_cannot_be_read)
{
    // Mid point between min and max
    const double target = getMidBrightness();

    fake_abc_ioService_failReads(true);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_ioService_getNumWrites());
}

TEST_F(abc_backlight_controller, brightness_is_not_set_when_the_new_value_is_the_same_as_the_old_value)
{
    abc_backlightBrightnessController_set((fake_abc_ioService_getCurrentBrightness() * 100.0) / s_DEFAULT_RAW_MAX);

    ASSERT_EQ(0, fake_abc_ioService_getNumWrites());
}

TEST_F(abc_backlight_controller, setting_the_number_of_brightness_increments_to_0_fails)
{
    ASSERT_FALSE(abc_backlightBrightnessController_setNumIncrements(0));
}

TEST_F(abc_backlight_controller, setting_the_brightness_increment_period_to_0_causes_the_brightness_to_be_set_with_one_write)
{
    abc_backlightBrightnessController_setIncrementsPeriod_ms(0);

    abc_backlightBrightnessController_set((getMidBrightness() / 100.0) * (double)s_DEFAULT_RAW_MAX);

    ASSERT_EQ(1, fake_abc_ioService_getNumWrites());
}
