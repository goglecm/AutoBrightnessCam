#include "abc_power_controller/abc_power_controller.h"
#include "abc_brightness_service/fake_abc_power_controller.h"

#include <stdbool.h>

typedef fake_abc_PowerState_t PowerState_t;

static PowerState_t
s_source = FAKE_ABC_POWERSTATE_DISCHARGING;

void
fake_abc_powerController_setState(const PowerState_t source)
{
    s_source = source;
}

bool
abc_powerController_isCharging(void)
{
    return FAKE_ABC_POWERSTATE_CHARGING == s_source;
}
