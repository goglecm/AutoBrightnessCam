#include "abc_ambient_controller/abc_ambient_controller.h"
#include "abc_brightness_service/fake_abc_ambient_controller.h"

#include <assert.h>
#include <stdbool.h>

static double
s_value;

static bool
s_isValueSet = false;

bool
abc_ambientBrightnessController_get(double *const restrict pResult)
{
    assert(s_isValueSet);
    assert(pResult);

    *pResult = s_value;

    return true;
}

void
fake_abc_ambientBrightnessController_set(double value)
{
    s_value = value;

    s_isValueSet = true;
}
