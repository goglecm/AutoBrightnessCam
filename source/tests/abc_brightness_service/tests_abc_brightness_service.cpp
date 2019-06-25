#include <gtest/gtest.h>

#include "abc_brightness_service.h"

#include "fake_abc_ambient_brightness_controller.h"
#include "fake_abc_backlight_brightness_controller.h"
#include "abc_backlight_brightness_controller.h"
#include "fake_abc_time_service.h"
#include "fake_abc_power_controller.h"

const abc_brightnessService_PeriodSec_t s_TEST_DEFAULT_PERIOD_SEC = 30;

const double s_TEST_DEFAULT_AMBIENT_BRIGHTNESS = 30;

const double s_TEST_DEFAULT_BACKLIGHT_BRIGHTNESS = 20;

static bool
isAtIntegerLimit(const abc_brightnessService_PeriodSec_t period)
{
    return (~period) == 0;
}

class abc_brightness_service: public ::testing::Test
{

public:
    abc_brightness_service(void)
    {
        // initialization code here
    }

    void SetUp(void)
    {
        // code here will execute just before the test ensues

        abc_brightnessService_stop();

        abc_brightnessService_setPeriod(s_TEST_DEFAULT_PERIOD_SEC);

        fake_abc_powerController_setState(fake_abc_PowerState_DISCHARGING);

        abc_backlightBrightnessController_set(s_TEST_DEFAULT_BACKLIGHT_BRIGHTNESS);

        fake_abc_ambientBrightnessController_set(s_TEST_DEFAULT_AMBIENT_BRIGHTNESS);
    }

    void TearDown(void)
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be

        abc_brightnessService_stop();

    }

    ~abc_brightness_service(void)
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
};

TEST(abc_brightness_service_initial_conditions, minimum_period_is_not_zero)
{
    ASSERT_NE(0, g_abc_brightnessService_MIN_PERIOD);
}

TEST(abc_brightness_service_initial_conditions, default_period_between_the_min_and_max_periods)
{
    ASSERT_GE(g_abc_brightnessService_DEFAULT_PERIOD,
              g_abc_brightnessService_MIN_PERIOD);

    ASSERT_LE(g_abc_brightnessService_DEFAULT_PERIOD,
              g_abc_brightnessService_MAX_PERIOD);
}

TEST(abc_brightness_service_period, period_is_set_when_the_service_is_not_running)
{
    abc_brightnessService_stop();

    ASSERT_EQ(abc_brightnessService_SUCCESS,
              abc_brightnessService_setPeriod(s_TEST_DEFAULT_PERIOD_SEC));

    ASSERT_EQ(s_TEST_DEFAULT_PERIOD_SEC, abc_brightnessService_getPeriod());
}

TEST(abc_brightness_service_period, period_is_not_set_when_the_service_is_running)
{
    abc_brightnessService_start();

    ASSERT_EQ(abc_brightnessService_FAILURE,
              abc_brightnessService_setPeriod(s_TEST_DEFAULT_PERIOD_SEC));
}

TEST(abc_brightness_service_period, period_is_not_set_lower_than_the_minimum_period)
{
    abc_brightnessService_stop();

    const abc_brightnessService_PeriodSec_t belowMinimum =
        g_abc_brightnessService_MIN_PERIOD - 1;

    ASSERT_EQ(abc_brightnessService_FAILURE,
              abc_brightnessService_setPeriod(belowMinimum));
}

TEST(abc_brightness_service_period, period_is_not_set_higher_than_the_maximum_period)
{
    if (isAtIntegerLimit(g_abc_brightnessService_MAX_PERIOD))
    {
        // The maximum period is set to the ceil limit of the type.
        SUCCEED();
    }

    abc_brightnessService_stop();

    const abc_brightnessService_PeriodSec_t aboveMax =
        g_abc_brightnessService_MAX_PERIOD + 1;

    ASSERT_EQ(abc_brightnessService_FAILURE,
              abc_brightnessService_setPeriod(aboveMax));
}

TEST_F(abc_brightness_service, service_reports_error_if_woken_when_not_started)
{
    ASSERT_EQ(abc_brightnessService_FAILURE, abc_brightnessService_wakeUp());
}

TEST_F(abc_brightness_service, backlight_brightness_is_set_to_the_ambient_brightness_6_times_during_6_periods)
{
    const abc_brightnessService_PeriodSec_t period = 5;

    const unsigned numPeriods = 6;

    abc_brightnessService_setPeriod(period);

    abc_brightnessService_start();

    fake_abc_BacklightBrightnessValue_t brightnessAtPeriodStart =
        fake_abc_backlightBrightnessController_get();

    for (unsigned timeNow = 0; timeNow < period * numPeriods; ++timeNow)
    {
        const double ambientBrightness = timeNow + s_TEST_DEFAULT_BACKLIGHT_BRIGHTNESS;

        fake_abc_ambientBrightnessController_set(ambientBrightness);

        fake_abc_timeService_forward(1);

        EXPECT_EQ(abc_brightnessService_SUCCESS,
                  abc_brightnessService_wakeUp());

        const fake_abc_BacklightBrightnessValue_t backlightBrightness =
            fake_abc_backlightBrightnessController_get();

        if ((timeNow + 1) % period == 0)
        {
            EXPECT_EQ(FAKE_ABC_BACKLIGHT_BRIGHTNESS_SET,
                      backlightBrightness.set);

            EXPECT_DOUBLE_EQ(ambientBrightness,
                             backlightBrightness.value);

            brightnessAtPeriodStart = backlightBrightness;
        }
        else
        {
            EXPECT_EQ(brightnessAtPeriodStart.set,
                      backlightBrightness.set);

            EXPECT_DOUBLE_EQ(brightnessAtPeriodStart.value,
                             backlightBrightness.value);
        }
    }
}

TEST_F(abc_brightness_service, backlight_brightness_is_not_changed_if_service_is_woken_when_not_started)
{
    fake_abc_timeService_forward(2 * s_TEST_DEFAULT_PERIOD_SEC);

    ASSERT_EQ(abc_brightnessService_FAILURE, abc_brightnessService_wakeUp());

    ASSERT_NE(s_TEST_DEFAULT_AMBIENT_BRIGHTNESS, fake_abc_backlightBrightnessController_get().value);
}

TEST_F(abc_brightness_service, backlight_brightness_is_set_to_maximum_when_charging)
{
    fake_abc_powerController_setState(fake_abc_PowerState_CHARGING);

    abc_brightnessService_start();

    fake_abc_timeService_forward(2 * s_TEST_DEFAULT_PERIOD_SEC);

    ASSERT_EQ(abc_brightnessService_SUCCESS, abc_brightnessService_wakeUp());

    const fake_abc_BacklightBrightnessValue_t
        actualBrightness = fake_abc_backlightBrightnessController_get();

    ASSERT_EQ(FAKE_ABC_BACKLIGHT_BRIGHTNESS_SET, actualBrightness.set);

    ASSERT_DOUBLE_EQ(g_abc_BacklightBrightnessController_MAX,
                     actualBrightness.value);
}

TEST_F(abc_brightness_service, backlight_brightness_does_not_exceed_maximum_brightness)
{
    fake_abc_ambientBrightnessController_set(2 * g_abc_BacklightBrightnessController_MAX);

    abc_brightnessService_start();

    fake_abc_timeService_forward(2 * s_TEST_DEFAULT_PERIOD_SEC);

    ASSERT_EQ(abc_brightnessService_SUCCESS, abc_brightnessService_wakeUp());

    const fake_abc_BacklightBrightnessValue_t
        actualBrightness = fake_abc_backlightBrightnessController_get();

    ASSERT_EQ(FAKE_ABC_BACKLIGHT_BRIGHTNESS_SET, actualBrightness.set);

    ASSERT_LE(actualBrightness.value,
              g_abc_BacklightBrightnessController_MAX);
}

TEST_F(abc_brightness_service, backlight_brightness_does_not_recede_minimum_brightness)
{
    fake_abc_ambientBrightnessController_set(g_abc_BacklightBrightnessController_MIN / 2);

    abc_brightnessService_start();

    fake_abc_timeService_forward(2 * s_TEST_DEFAULT_PERIOD_SEC);

    ASSERT_EQ(abc_brightnessService_SUCCESS, abc_brightnessService_wakeUp());

    const fake_abc_BacklightBrightnessValue_t
        actualBrightness = fake_abc_backlightBrightnessController_get();

    ASSERT_EQ(FAKE_ABC_BACKLIGHT_BRIGHTNESS_SET, actualBrightness.set);

    ASSERT_GE(actualBrightness.value,
              g_abc_BacklightBrightnessController_MIN);
}
