// Be very strict on the values of ABC_HAS_UPOWER.
#ifndef ABC_HAS_UPOWER
#   error Please define ABC_HAS_UPOWER.
#else
#   if ABC_HAS_UPOWER != 0 && ABC_HAS_UPOWER != 1
#       error Possible values are either 0 or 1.
#   endif // if ABC_HAS_UPOWER != 0 && ABC_HAS_UPOWER != 1
#endif // #ifndef ABC_HAS_UPOWER


#include <gtest/gtest.h>

#include "abc_power_controller/abc_power_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include "testlib_io.h"


#if ABC_HAS_UPOWER == 1
#   include "abc_power_controller/fake_abc_terminal_controller.h"
#else
#   include "abc_power_controller/fake_abc_io_service.h"
#endif // #if ABC_HAS_UPOWER == 1


typedef abc_powerController_State_t ChargingState_t;


class abc_power_controller_states: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        std::string logName(SPECIFIC_LOG_NAME);
        const std::string tail(ABC_HAS_UPOWER ? "_with_upower" : "_without_upower");

        logName.insert(logName.find(".log"), tail);

        ASSERT_TRUE(abc_loggingService_setLogName(logName.c_str()));

        ABC_LOG("\n ## Starting test %s ##\n",
                ::testing::UnitTest::GetInstance()->current_test_info()->name());

#if ABC_HAS_UPOWER == 1

        fake_abc_terminalController_resetStates();

#else

        abc_powerController_resetBatteryStatePath();

        fake_abc_ioService_resetStates();

        fake_abc_ioService_setBatteryStatePath("/sys/class/power_supply/BAT1/status");

#endif // #if ABC_HAS_UPOWER == 1

    }
};

#if ABC_HAS_UPOWER == 0

class abc_power_controller_filepaths: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName(SPECIFIC_LOG_NAME));

        ABC_LOG("\n ## Starting test %s ##\n",
                ::testing::UnitTest::GetInstance()->current_test_info()->name());

        ASSERT_EQ(ABC_HAS_UPOWER, 0);

        fake_abc_ioService_resetStates();

        abc_powerController_resetBatteryStatePath();
    }
};

#endif // #if ABC_HAS_UPOWER == 0

static inline void
setState(const ChargingState_t state)
{

#if ABC_HAS_UPOWER == 1

    fake_abc_terminalController_setUpowerState(state);

#else

    fake_abc_ioService_setBatteryState(state);

#endif // #if ABC_HAS_UPOWER == 1

}

static inline void
checkIfStateWasRead(void)
{

#if ABC_HAS_UPOWER == 1

    ASSERT_TRUE(fake_abc_terminalController_calledUpower());

#else

    ASSERT_TRUE(fake_abc_ioService_wasStateRead());

#endif // #if ABC_HAS_UPOWER == 1

}

TEST_F(abc_power_controller_states, battery_is_discharging_when_the_battery_reports_discharging)
{
    setState(ABC_POWER_CONTROLLER_STATE_DISCHARGING);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_FALSE(isCharging);
}

TEST_F(abc_power_controller_states, battery_is_charging_when_the_battery_reports_charging)
{
    setState(ABC_POWER_CONTROLLER_STATE_CHARGING);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_TRUE(isCharging);
}

TEST_F(abc_power_controller_states, battery_is_charging_when_the_battery_reports_fully_charged)
{
    setState(ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_TRUE(isCharging);
}

TEST_F(abc_power_controller_states, battery_is_discharging_when_the_charging_state_cannot_be_determined)
{
    setState(ABC_POWER_CONTROLLER_STATE_UNKNOWN);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_FALSE(isCharging);
}

#if ABC_HAS_UPOWER == 0

TEST_F(abc_power_controller_filepaths, battery_state_is_unknown_when_the_battery_state_path_cannot_be_determined)
{
    fake_abc_ioService_setBatteryStatePath("/bad/battery/path");

    setState(ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED);

    (void) abc_powerController_isCharging();

    ASSERT_FALSE(fake_abc_ioService_wasStateRead());
}

TEST_F(abc_power_controller_filepaths, battery_state_path_at_sys_class_power_supply_BAT1_is_read)
{
    fake_abc_ioService_setBatteryStatePath("/sys/class/power_supply/BAT1/status");

    setState(ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED);

    (void) abc_powerController_isCharging();

    checkIfStateWasRead();
}

TEST_F(abc_power_controller_filepaths, battery_state_path_at_sys_class_power_supply_BAT0_is_read)
{
    fake_abc_ioService_setBatteryStatePath("/sys/class/power_supply/BAT0/status");

    setState(ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED);

    (void) abc_powerController_isCharging();

    checkIfStateWasRead();
}

TEST_F(abc_power_controller_filepaths, battery_state_path_at_proc_acpi_battery_BAT0_is_read)
{
    fake_abc_ioService_setBatteryStatePath("/proc/acpi/battery/BAT0/status");

    setState(ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED);

    (void) abc_powerController_isCharging();

    checkIfStateWasRead();
}

#endif // #if ABC_HAS_UPOWER == 0
