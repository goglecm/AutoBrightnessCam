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


class abc_power_controller: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        const std::string
            logName = std::string(SPECIFIC_LOG_NAME) +
                      (ABC_HAS_UPOWER ? "_with_upower" : "_without_upower");

        ASSERT_TRUE(abc_loggingService_setLogName(logName.c_str()));

        ABC_LOG("\n ## Starting test %s ## \n",
                ::testing::UnitTest::GetInstance()->current_test_info()->name());

#if ABC_HAS_UPOWER == 1

        fake_abc_terminalController_resetStates();

#else

        fake_abc_ioService_resetStates();

#endif // #if ABC_HAS_UPOWER == 1

    }
};

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

TEST_F(abc_power_controller, battery_is_discharging_when_the_battery_reports_discharging)
{
    setState(ABC_POWER_CONTROLLER_STATE_DISCHARGING);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_FALSE(isCharging);
}

TEST_F(abc_power_controller, battery_is_charging_when_the_battery_reports_charging)
{
    setState(ABC_POWER_CONTROLLER_STATE_CHARGING);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_TRUE(isCharging);
}

TEST_F(abc_power_controller, battery_is_charging_when_the_battery_reports_fully_charged)
{
    setState(ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_TRUE(isCharging);
}

TEST_F(abc_power_controller, battery_is_discharging_when_the_charging_state_cannot_be_determined)
{
    setState(ABC_POWER_CONTROLLER_STATE_UNKNOWN);

    const bool isCharging = abc_powerController_isCharging();

    checkIfStateWasRead();

    ASSERT_FALSE(isCharging);
}

