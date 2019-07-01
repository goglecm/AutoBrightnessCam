#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_power_controller/fake_abc_terminal_controller.h"

#include <assert.h>
#include <string.h>

static bool
s_isCharging;

static bool
s_isChargingStateSet = false;

static bool
s_isUpowerCalled = false;

void
fake_abc_terminalController_setUpowerState(const bool isCharging)
{
    s_isCharging = isCharging;

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
    for (unsigned i = 0; i < sizeof(upowerStr) - 1; ++i)
    {
        if (upowerStr[i] != pCmd[i])
        {
            isUpowerCalled = false;
            break;
        }
    }

    s_isUpowerCalled = isUpowerCalled;

    // Report the result.
    if (s_isCharging)
    {
        strcpy(pResult, "charging\n");
    }
    else
    {
        strcpy(pResult, "discharging\n");
    }

    return true;
}
