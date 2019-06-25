#include "abc_backlight_brightness_controller.h"

#include "fake_abc_backlight_brightness_controller.h"

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
}

fake_abc_BacklightBrightnessValue_t
fake_abc_backlightBrightnessController_get(void)
{
    return s_value;
}
