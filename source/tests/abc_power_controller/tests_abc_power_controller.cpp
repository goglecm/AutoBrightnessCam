#include <gtest/gtest.h>

#include "abc_power_controller/abc_power_controller.h"

#include "abc_power_controller/fake_abc_terminal_controller.h"

TEST(abc_power_controller, battery_is_discharging_when_upower_reports_discharging)
{
    fake_abc_terminalController_setUpowerState(FAKE_ABC_TERMINAL_CONTROLLER_STATE_DISCHARGING);

    const bool isCharging = abc_powerController_isCharging();

    ASSERT_TRUE(fake_abc_terminalController_calledUpower());

    ASSERT_FALSE(isCharging);
}

TEST(abc_power_controller, battery_is_charging_when_upower_reports_charging)
{
    fake_abc_terminalController_setUpowerState(FAKE_ABC_TERMINAL_CONTROLLER_STATE_CHARGING);

    const bool isCharging = abc_powerController_isCharging();

    ASSERT_TRUE(fake_abc_terminalController_calledUpower());

    ASSERT_TRUE(isCharging);
}

TEST(abc_power_controller, battery_is_discharging_when_the_charging_state_cannot_be_determined)
{
    fake_abc_terminalController_setUpowerState(FAKE_ABC_TERMINAL_CONTROLLER_STATE_UNKNOWN);

    const bool isCharging = abc_powerController_isCharging();

    ASSERT_TRUE(fake_abc_terminalController_calledUpower());

    ASSERT_FALSE(isCharging);
}
