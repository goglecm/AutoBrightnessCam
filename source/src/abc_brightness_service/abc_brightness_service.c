#include "abc_brightness_service.h"

#include <assert.h>
#include <stdbool.h>

#include "abc_time_service.h"
#include "abc_ambient_brightness_controller.h"
#include "abc_backlight_brightness_controller.h"
#include "abc_power_controller.h"

#define ABC_DEFAULT_PERIOD (5U)

static abc_brightnessService_Status_t
s_status = abc_brightnessService_STOPPED;

static abc_brightnessService_PeriodSec_t
s_period = ABC_DEFAULT_PERIOD;

static time_t s_lastTimestamp;

const abc_brightnessService_PeriodSec_t
g_abc_brightnessService_DEFAULT_PERIOD = ABC_DEFAULT_PERIOD;

const abc_brightnessService_PeriodSec_t
g_abc_brightnessService_MIN_PERIOD = 1;

const abc_brightnessService_PeriodSec_t
g_abc_brightnessService_MAX_PERIOD = 1800;

abc_brightnessService_PeriodSec_t
abc_brightnessService_getPeriod(void)
{
    return s_period;
}

static int
isPeriodValid(const abc_brightnessService_PeriodSec_t period)
{
    return period >= g_abc_brightnessService_MIN_PERIOD &&
           period <= g_abc_brightnessService_MAX_PERIOD;
}

static bool
isStopped(void)
{
    return abc_brightnessService_STOPPED == s_status;
}

static bool
isNextPeriod(const time_t now)
{
    return (s_lastTimestamp + s_period) <= now;
}

abc_brightnessService_Result_t
abc_brightnessService_setPeriod(const abc_brightnessService_PeriodSec_t period)
{
    if (isStopped() && isPeriodValid(period))
    {
        s_period = period;

        return abc_brightnessService_SUCCESS;
    }

    return abc_brightnessService_FAILURE;
}

void
abc_brightnessService_stop(void)
{
    s_status = abc_brightnessService_STOPPED;
}

void
abc_brightnessService_start(void)
{
    s_status = abc_brightnessService_STARTED;

    s_lastTimestamp = abc_timeService_get();

    const abc_brightnessService_Result_t result = abc_brightnessService_wakeUp();

    assert(abc_brightnessService_SUCCESS == result);
}

abc_brightnessService_Result_t
abc_brightnessService_wakeUp(void)
{
    if (isStopped())
    {
        return abc_brightnessService_FAILURE;
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

    return abc_brightnessService_SUCCESS;
}
