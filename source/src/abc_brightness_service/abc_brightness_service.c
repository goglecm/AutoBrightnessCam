#include "abc_brightness_service/abc_brightness_service.h"

#include "abc_time_service/abc_time_service.h"
#include "abc_ambient_brightness_controller/abc_ambient_brightness_controller.h"
#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"
#include "abc_power_controller/abc_power_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdbool.h>

#define ABC_DEFAULT_PERIOD (5U)

typedef abc_brightnessService_PeriodSec_t PeriodSec_t;

typedef abc_brightnessService_Result_t Result_t;

static abc_brightnessService_Status_t
s_status = ABC_BRIGHTNESSSERVICE_STOPPED;

static PeriodSec_t
s_period = ABC_DEFAULT_PERIOD;

static time_t s_lastTimestamp;

const PeriodSec_t
g_abc_brightnessService_DEFAULT_PERIOD = ABC_DEFAULT_PERIOD;

const PeriodSec_t
g_abc_brightnessService_MIN_PERIOD = 1;

const PeriodSec_t
g_abc_brightnessService_MAX_PERIOD = 1800;

PeriodSec_t
abc_brightnessService_getPeriod(void)
{
    return s_period;
}

static int
isValid(const PeriodSec_t period)
{
    return period >= g_abc_brightnessService_MIN_PERIOD &&
           period <= g_abc_brightnessService_MAX_PERIOD;
}

static bool
isStopped(void)
{
    return ABC_BRIGHTNESSSERVICE_STOPPED == s_status;
}

static bool
isNextPeriod(const time_t now)
{
    return (s_lastTimestamp + s_period) <= now;
}

Result_t
abc_brightnessService_setPeriod(const PeriodSec_t period)
{
    if (isStopped() && isValid(period))
    {
        s_period = period;

        return ABC_BRIGHTNESSSERVICE_SUCCESS;
    }

    ABC_LOG_WRN("failed to set period, isStopped = %u, isValid = %u",
                isStopped(), isValid(period));

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
        return ABC_BRIGHTNESSSERVICE_FAILURE;
    }

    if (abc_powerController_isCharging())
    {
        abc_backlightBrightnessController_set(g_abc_BacklightBrightnessController_MAX);
    }
    else
    {
        const time_t now = abc_timeService_get();

        if (isNextPeriod(now))
        {
            const double ambientBrightness = abc_ambientBrightnessController_get();

            abc_backlightBrightnessController_set(ambientBrightness);

            s_lastTimestamp = now;
        }
    }

    return ABC_BRIGHTNESSSERVICE_SUCCESS;
}
