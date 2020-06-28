#include "abc_backlight_controller/abc_backlight_controller.h"
#include "abc_brightness_service/fake_abc_backlight_controller.h"

typedef fake_abc_BacklightBrightnessValue_t RawValue_t;

static unsigned
s_numSetCalls;

static RawValue_t
    s_value =
    {
        .value = 0,
        .set = FAKE_ABC_BACKLIGHT_BRIGHTNESS_NOT_SET
    };

double
abc_backlightBrightnessController_getMax(void)
{
    return 100;
}

double
abc_backlightBrightnessController_getMin(void)
{
    return 5;
}

void
abc_backlightBrightnessController_set(const double value)
{
    s_value.value = value;
    s_value.set = FAKE_ABC_BACKLIGHT_BRIGHTNESS_SET;

    s_numSetCalls++;
}

RawValue_t
fake_abc_backlightBrightnessController_get(void)
{
    return s_value;
}

unsigned
fake_abc_backlightBrightnessController_numSetCalls(void)
{
    return s_numSetCalls;
}

void
fake_abc_backlightBrightnessController_resetNumSetCalls(void)
{
    s_numSetCalls = 0;
}
