#include "abc_brightness_service/abc_brightness_service.h"

#include "abc_time_service/abc_time_service.h"
#include "abc_ambient_brightness_controller/abc_ambient_brightness_controller.h"
#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"
#include "abc_power_controller/abc_power_controller.h"
#include "abc_logging_service/abc_logging_service.h"
#include "abc_filter/abc_filter.h"

#include <stdbool.h>

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

    if (ABC_BRIGHTNESSSERVICE_SUCCESS != abc_brightnessService_wakeUp())
    {
        ABC_LOG_ERR("service started but it failed to wakeup properly, "
                    "further wakeups may or may not fail");
    }

    s_status = ABC_BRIGHTNESSSERVICE_STARTED;
}

Result_t
abc_brightnessService_wakeUp(void)
{
    if (isStopped())
    {
        ABC_LOG_ERR("failed to wake up, service stopped");

        return ABC_BRIGHTNESSSERVICE_FAILURE;
    }

    // When charging, the brightness is at max.
    if (abc_powerController_isCharging())
    {
        abc_backlightBrightnessController_set(g_abc_BacklightBrightnessController_MAX);

        return ABC_BRIGHTNESSSERVICE_SUCCESS;
    }

    // Wait until one period has passed since the last timestamp.
    const time_t now = abc_timeService_get();
    const bool isAtNextPeriod = (s_lastTimestamp + s_period) <= now;
    if (!isAtNextPeriod)
    {
        return ABC_BRIGHTNESSSERVICE_SUCCESS;
    }

    // Update the timestamp to work out the next period.
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
