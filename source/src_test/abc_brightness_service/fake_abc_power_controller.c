#include "abc_power_controller.h"

#include "fake_abc_power_controller.h"

static fake_abc_PowerState_t
s_source = fake_abc_PowerState_DISCHARGING;

void
fake_abc_powerController_setState(const fake_abc_PowerState_t source)
{
    s_source = source;
}

bool
abc_powerController_isCharging(void)
{
    return fake_abc_PowerState_CHARGING == s_source;
}
