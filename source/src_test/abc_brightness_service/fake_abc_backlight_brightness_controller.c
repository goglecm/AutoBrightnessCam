#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"
#include "abc_brightness_service/fake_abc_backlight_brightness_controller.h"

static unsigned s_numSetCalls;

const double g_abc_BacklightBrightnessController_MAX = 100;

const double g_abc_BacklightBrightnessController_MIN = 10;

static fake_abc_BacklightBrightnessValue_t s_value = {
    .value = 0,
    .set = FAKE_ABC_BACKLIGHT_BRIGHTNESS_NOT_SET
};

void
abc_backlightBrightnessController_set(const double value)
{
    s_value.value = value;
    s_value.set = FAKE_ABC_BACKLIGHT_BRIGHTNESS_SET;

    s_numSetCalls++;
}

fake_abc_BacklightBrightnessValue_t
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
