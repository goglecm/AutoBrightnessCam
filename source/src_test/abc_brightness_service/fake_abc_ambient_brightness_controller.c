#include "abc_ambient_brightness_controller/abc_ambient_brightness_controller.h"
#include "abc_brightness_service/fake_abc_ambient_brightness_controller.h"

#include <assert.h>
#include <stdbool.h>

static double s_value;

static bool s_isValueSet = false;

double abc_ambientBrightnessController_get(void)
{
    assert(s_isValueSet);

    return s_value;
}

void fake_abc_ambientBrightnessController_set(double value)
{
    s_value = value;

    s_isValueSet = true;
}
