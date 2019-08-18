#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_power_controller/fake_abc_terminal_controller.h"

#include <assert.h>
#include <string.h>

static fake_abc_terminalController_ChargingState_t
s_chargingState;

static bool
s_isChargingStateSet = false;

static bool
s_isUpowerCalled = false;

void
fake_abc_terminalController_setUpowerState(const fake_abc_terminalController_ChargingState_t chargingState)
{
    s_chargingState = chargingState;

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
    assert(pResult);
    assert(pCmd);
    assert(s_isChargingStateSet);
    assert(resultLen > sizeof("discharging"));

    const char upowerStr[] = "upower";

    // Compare the strings.
    bool isUpowerCalled = true;
    for (size_t i = 0; i < sizeof(upowerStr) - 1; ++i)
    {
        if (upowerStr[i] != pCmd[i])
        {
            isUpowerCalled = false;
            break;
        }
    }

    s_isUpowerCalled = isUpowerCalled;

    bool result = true;

    // Report the result.
    switch (s_chargingState)
    {
        case FAKE_ABC_TERMINAL_CONTROLLER_STATE_CHARGING:
            strcpy(pResult, "charging\n");
            break;

        case FAKE_ABC_TERMINAL_CONTROLLER_STATE_DISCHARGING:
            strcpy(pResult, "discharging\n");
            break;

        case FAKE_ABC_TERMINAL_CONTROLLER_STATE_FULLY_CHARGED:
            strcpy(pResult, "fully-charged\n");
            break;

        default:
            strcpy(pResult, "unknown");
            result = false;
            break;
    }

    return result;
}
