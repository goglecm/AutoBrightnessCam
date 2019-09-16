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

static char
s_batteryStatePath[128] = { 0 };

void
fake_abc_ioService_setBatteryStatePath(const char *const restrict pFileName)
{
    assert(pFileName);

    const size_t filenameLen = 1 + strnlen(pFileName, sizeof(s_batteryStatePath) - 1);

    assert(filenameLen < sizeof(s_batteryStatePath));

    memcpy(s_batteryStatePath, pFileName, filenameLen);

    ABC_LOG("new battery state path = `%s`", s_batteryStatePath);
}

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
    ABC_LOG("resetting read state, state set and batteryPath");

    s_wasStateRead = false;
    s_wasStateSet  = false;

    memset(s_batteryStatePath, 0, sizeof(s_batteryStatePath));
}

bool
abc_ioService_exists(const char *const restrict pFileName)
{
    assert(pFileName && s_wasStateSet && s_batteryStatePath[0]);

    return 0 == memcmp(pFileName,
                       s_batteryStatePath,
                       1 + strnlen(pFileName, sizeof(s_batteryStatePath) - 1));
}

bool
abc_ioService_readStr(char *const restrict pBuf,
                      const int bufMaxLen,
                      const char *const restrict pFileName)
{
    assert(pBuf && pFileName && bufMaxLen > 16 && s_wasStateSet && s_batteryStatePath[0]);

    const size_t filenameLen = 1 + strnlen(pFileName, sizeof(s_batteryStatePath) - 1);

    if (0 != memcmp(pFileName, s_batteryStatePath, filenameLen))
    {
        ABC_LOG_WRN("battery path `%s` doesn't match the expected battery path `%s`",
                    pFileName, s_batteryStatePath);

        return false;
    }

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
