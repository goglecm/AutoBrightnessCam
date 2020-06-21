#include "abc_power_controller/abc_power_controller.h"

#include <stdio.h>
#include <string.h>

#include "abc_logging_service/abc_logging_service.h"


#ifndef ABC_HAS_UPOWER

#error "ABC_HAS_UPOWER is not defined"

#endif // ABC_HAS_UPOWER


#if ABC_HAS_UPOWER != 0 && ABC_HAS_UPOWER != 1

#error "Bad value for ABC_HAS_UPOWER"

#endif // ABC_HAS_UPOWER


#if ABC_HAS_UPOWER == 1
#   include "abc_terminal_controller/abc_terminal_controller.h"
#else
#   include "abc_io_service/abc_io_service.h"
#endif // ABC_HAS_UPOWER


#define BUFF_SIZE 128U

#define NUM_STATUS_PATHS 3U

typedef abc_powerController_State_t BatteryState_t;


#if ABC_HAS_UPOWER == 0

static char
s_batteryStatePath[BUFF_SIZE];

static bool
s_isBatteryStatePathSet = false;

static bool
setBatteryStatePath(void)
{
    static const char *batteryStatusPaths[NUM_STATUS_PATHS] =
    {
        "/sys/class/power_supply/BAT1/status",
        "/sys/class/power_supply/BAT0/status",
        "/proc/acpi/battery/BAT0/status",
    };

    for (size_t strNo = 0; strNo < NUM_STATUS_PATHS; ++strNo)
    {
        if (abc_ioService_exists(batteryStatusPaths[strNo]))
        {
            memcpy(s_batteryStatePath,
                   batteryStatusPaths[strNo],
                   1 + strlen(batteryStatusPaths[strNo]));

            s_isBatteryStatePathSet = true;

            ABC_LOG("found battery path = `%s` from `%s`",
                    s_batteryStatePath, batteryStatusPaths[strNo]);

            return true;
        }
    }

    ABC_LOG_ERR("none of the battery paths exist");

    return false;
}

#endif // #if ABC_HAS_UPOWER == 0

static BatteryState_t
getStatus(void)
{
    static char s_batteryStateStr[BUFF_SIZE];

#if ABC_HAS_UPOWER == 1

    static const char chargingStr[]     = "charging";
    static const char dischargingStr[]  = "discharging";
    static const char fullyChargedStr[] = "fully-charged";

    static const char cmd[] = "upower -i `upower -e | "
                              "fgrep 'BAT'` | "
                              "fgrep state | "
                              "sed 's^state:^^g' | "
                              "sed 's^ ^^g'";

    const bool isStateValid =
        abc_terminalController_sendReturnStr(BUFF_SIZE, s_batteryStateStr, cmd);

#else

    static const char chargingStr[]     = "Charging";
    static const char dischargingStr[]  = "Discharging";
    static const char fullyChargedStr[] = "Fully-charged";

    if (!s_isBatteryStatePathSet)
    {
        if (!setBatteryStatePath())
        {
            ABC_LOG_ERR("failed to set battery state path");
        }
    }

    bool isStateValid = false;
    if (s_isBatteryStatePathSet)
    {
        isStateValid =
            abc_ioService_readStr(s_batteryStateStr, BUFF_SIZE - 1, s_batteryStatePath);
    }

#endif // #if ABC_HAS_UPOWER == 1

    if (!isStateValid)
    {
        ABC_LOG_ERR("Failed to get the charging state, returning unknown");

        return ABC_POWER_CONTROLLER_STATE_UNKNOWN;
    }

    // At this point the read str should be NULL terminated.
    // Remove the newline from the end of the string.
    s_batteryStateStr[strnlen(s_batteryStateStr, BUFF_SIZE - 1) - 1] = '\0';

    // Determine state.
    BatteryState_t state;
    if (0 == strcmp(dischargingStr, s_batteryStateStr))
    {
        state = ABC_POWER_CONTROLLER_STATE_DISCHARGING;
    }
    else if (0 == strcmp(fullyChargedStr, s_batteryStateStr))
    {
        state = ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED;
    }
    else if (0 == strcmp(chargingStr, s_batteryStateStr))
    {
        state = ABC_POWER_CONTROLLER_STATE_CHARGING;
    }
    else
    {
        state = ABC_POWER_CONTROLLER_STATE_UNKNOWN;
    }

    ABC_LOG("battery state(%d) = `%s`", state, s_batteryStateStr);

    return state;
}

void
abc_powerController_resetBatteryStatePath(void)
{

#if ABC_HAS_UPOWER == 0

    memset(s_batteryStatePath, 0, sizeof(s_batteryStatePath));

    s_isBatteryStatePathSet = false;

#endif // #if ABC_HAS_UPOWER == 0

}

bool
abc_powerController_isCharging(void)
{
    const BatteryState_t state = getStatus();

    return state == ABC_POWER_CONTROLLER_STATE_CHARGING ||
           state == ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED;
}

