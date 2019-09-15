#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_power_controller/fake_abc_terminal_controller.h"

#include <assert.h>
#include <string.h>

#include "abc_logging_service/abc_logging_service.h"

typedef abc_powerController_State_t ChargingState_t;

static ChargingState_t
s_chargingState = ABC_POWER_CONTROLLER_STATE_UNKNOWN;

static bool
s_isChargingStateSet = false;

static bool
s_isUpowerCalled = false;

void
fake_abc_terminalController_resetStates(void)
{
    s_isUpowerCalled     = false;
    s_isChargingStateSet = false;
}

void
fake_abc_terminalController_setUpowerState(const ChargingState_t state)
{
    assert(state < ABC_POWER_CONTROLLER_STATE__COUNT);

    s_chargingState      = state;
    s_isChargingStateSet = true;
}

bool
fake_abc_terminalController_calledUpower(void)
{
    return s_isUpowerCalled;
}

bool
abc_terminalController_sendReturnStr(const unsigned resultLen,
                                     char *const restrict pResult,
                                     const char *const restrict pCmd)
{
    assert(pResult && pCmd && s_isChargingStateSet && resultLen > 16);

    const char upowerStr[] = "upower";

    // Compare the strings.
    if (0 != memcmp(upowerStr, pCmd, strlen(upowerStr)))
    {
        ABC_LOG_ERR("expecting a upower command");

        assert(false);
    }

    s_isUpowerCalled = true;

    bool result = true;

    // Report the result.
    switch (s_chargingState)
    {
        case ABC_POWER_CONTROLLER_STATE_CHARGING:
            strcpy(pResult, "charging\n");
            break;

        case ABC_POWER_CONTROLLER_STATE_DISCHARGING:
            strcpy(pResult, "discharging\n");
            break;

        case ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED:
            strcpy(pResult, "fully-charged\n");
            break;

        default:
            result = false;
            break;
    }

    ABC_LOG("result = %d, resultStr = `%s`", result, result ? pResult : "not set");

    return result;
}
