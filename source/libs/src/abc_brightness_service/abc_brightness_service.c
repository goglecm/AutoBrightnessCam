#include "abc_brightness_service/abc_brightness_service.h"

#include "abc_time_service/abc_time_service.h"
#include "abc_ambient_controller/abc_ambient_controller.h"
#include "abc_backlight_controller/abc_backlight_controller.h"
#include "abc_power_controller/abc_power_controller.h"
#include "abc_logging_service/abc_logging_service.h"
#include "abc_filter/abc_filter.h"

#define ABC_DEFAULT_PERIOD (5U)

#define ABC_FILTER_SIZE (8U)

typedef abc_brightnessService_PeriodSec_t PeriodSec_t;

typedef abc_brightnessService_Result_t Result_t;

static abc_brightnessService_Status_t
s_status = ABC_BRIGHTNESSSERVICE_STOPPED;

static PeriodSec_t
s_period = ABC_DEFAULT_PERIOD;

static time_t
s_lastTimestamp;

static bool
s_ignoreBattery = false;

static bool
s_isSetToMax = false;

const PeriodSec_t
g_abc_brightnessService_DEFAULT_PERIOD = ABC_DEFAULT_PERIOD;

const PeriodSec_t
g_abc_brightnessService_MIN_PERIOD = 1;

const PeriodSec_t
g_abc_brightnessService_MAX_PERIOD = 1800;

static bool
isStopped(void)
{
    return ABC_BRIGHTNESSSERVICE_STOPPED == s_status;
}

void
abc_brightnessService_ignoreBattery(const bool ignoreBattery)
{
    ABC_LOG("Ignore battery %d", ignoreBattery);

    s_ignoreBattery = ignoreBattery;
}

PeriodSec_t
abc_brightnessService_getPeriod(void)
{
    return s_period;
}

Result_t
abc_brightnessService_setPeriod(const PeriodSec_t period)
{
    const bool isValid = period >= g_abc_brightnessService_MIN_PERIOD &&
                         period <= g_abc_brightnessService_MAX_PERIOD;

    if (isStopped() && isValid)
    {
        s_period = period;

        return ABC_BRIGHTNESSSERVICE_SUCCESS;
    }

    ABC_LOG_ERR("failed to set period");

    return ABC_BRIGHTNESSSERVICE_FAILURE;
}

void
abc_brightnessService_stop(void)
{
    s_status = ABC_BRIGHTNESSSERVICE_STOPPED;
}

void
abc_brightnessService_start(void)
{
    s_lastTimestamp = abc_timeService_get();

    s_status = ABC_BRIGHTNESSSERVICE_STARTED;

    s_isSetToMax = false;

    if (ABC_BRIGHTNESSSERVICE_SUCCESS != abc_brightnessService_wakeUp())
    {
        ABC_LOG_ERR("service started but it failed to wakeup properly, "
                    "further wake ups may or may not fail");
    }
}

Result_t
abc_brightnessService_wakeUp(void)
{
    if (isStopped())
    {
        ABC_LOG_ERR("failed to wake up, service stopped");

        return ABC_BRIGHTNESSSERVICE_FAILURE;
    }


    ABC_LOG("Waking up");

    // When charging, the brightness is at max.
    if (!s_ignoreBattery && abc_powerController_isCharging())
    {
        ABC_LOG("Battery is charging");

        if (!s_isSetToMax)
        {
            ABC_LOG("Max brightness is not set");

            abc_backlightBrightnessController_set(abc_backlightBrightnessController_getMax());
            s_isSetToMax = true;
        }

        return ABC_BRIGHTNESSSERVICE_SUCCESS;
    }

    s_isSetToMax = false;

    // Wait until one period has passed since the last time stamp.
    const time_t now = abc_timeService_get();
    const bool isAtNextPeriod = (s_lastTimestamp + s_period) <= now;
    if (!isAtNextPeriod)
    {
        return ABC_BRIGHTNESSSERVICE_SUCCESS;
    }

    // Update the time stamp to work out the next period.
    s_lastTimestamp = now;

    double ambientBrightness = 0;
    if (!abc_ambientBrightnessController_get(&ambientBrightness))
    {
        ABC_LOG_ERR("failed to get ambient brightness");

        return ABC_BRIGHTNESSSERVICE_FAILURE;
    }

    static bool s_isInitialFilterStateSet = false;
    static double s_filterState[ABC_FILTER_SIZE];
    static abc_filter_AveragerData_t s_filter =
        {
            .SIZE = ABC_FILTER_SIZE,
            .internal_pos = 0,
            .pValues = &s_filterState[0],
        };

    // Initialise filter.
    if (!s_isInitialFilterStateSet)
    {
        for (uint16_t i = 0; i < ABC_FILTER_SIZE; ++i)
        {
            s_filterState[i] = ambientBrightness;
        }

        s_isInitialFilterStateSet = true;
    }

    // Get the average brightness.
    double meanValue = 0;
    if (!abc_filter_average(&s_filter, ambientBrightness, &meanValue))
    {
        ABC_LOG_ERR("failed to calculate the filter average");

        return ABC_BRIGHTNESSSERVICE_FAILURE;
    }

    abc_backlightBrightnessController_set(meanValue);

    return ABC_BRIGHTNESSSERVICE_SUCCESS;
}
