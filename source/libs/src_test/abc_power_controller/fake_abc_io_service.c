#include "abc_power_controller/fake_abc_io_service.h"
#include "abc_io_service/abc_io_service.h"

#include <assert.h>
#include <string.h>

#include "abc_logging_service/abc_logging_service.h"

typedef abc_powerController_State_t ChargingState_t;

static ChargingState_t
s_state = ABC_POWER_CONTROLLER_STATE_UNKNOWN;

static bool
s_wasStateRead = false;

static bool
s_wasStateSet = false;

void
fake_abc_ioService_setBatteryState(const ChargingState_t state)
{
    assert(state < ABC_POWER_CONTROLLER_STATE__COUNT);

    ABC_LOG("setting state to %d", state);

    s_state       = state;
    s_wasStateSet = true;
}

bool
fake_abc_ioService_wasStateRead(void)
{
    ABC_LOG("was state read = %d", s_wasStateRead);

    return s_wasStateRead;
}

void
fake_abc_ioService_resetStates(void)
{
    ABC_LOG("resetting read state and state set");

    s_wasStateRead = false;
    s_wasStateSet  = false;
}

bool
abc_ioService_readStr(char *const restrict pBuf,
                      const int bufMaxLen,
                      const char *const restrict pFileName)
{
    assert(pBuf && pFileName && bufMaxLen > 16 && s_wasStateSet);

    static const char chargingStr[]     = "Charging\n";
    static const char dischargingStr[]  = "Discharging\n";
    static const char fullyChargedStr[] = "Fully-charged\n";

    s_wasStateRead = true;

    ABC_LOG("reading state from `%s`, and state now is %d", pFileName, s_state);

    bool result = true;
    switch (s_state)
    {
        case ABC_POWER_CONTROLLER_STATE_DISCHARGING:
            memcpy(pBuf, dischargingStr, sizeof(dischargingStr));
            break;

        case ABC_POWER_CONTROLLER_STATE_CHARGING:
            memcpy(pBuf, chargingStr, sizeof(chargingStr));
            break;

        case ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED:
            memcpy(pBuf, fullyChargedStr, sizeof(fullyChargedStr));
            break;

        default:
            result = false;
    }

    ABC_LOG("result = %d, and retStr = `%s`", result, result ? pBuf : "not set");

    return result;
}
