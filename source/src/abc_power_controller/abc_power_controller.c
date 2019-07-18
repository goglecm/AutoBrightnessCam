#include "abc_power_controller/abc_power_controller.h"

#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#define BUFF_SIZE 32U

static const bool
s_DEFAULT_CHARGING_STATE = false;

bool
abc_powerController_isCharging(void)
{
    // todo: read /sys/class/power_supply/BAT1/status

    const char cmd[] = "upower -i `upower -e | "
                       "grep 'BAT'` | "
                       "grep state | "
                       "sed 's^state:^^g' | "
                       "sed 's^ ^^g'";

    const char chargingStr[] = "charging";
    const char dischargingStr[] = "discharging";

    char batteryStateStr[BUFF_SIZE] = {0};

    const unsigned bufferLen = sizeof(batteryStateStr);

    const bool isCmdSuccess =
        abc_terminalController_sendReturnStr(bufferLen, batteryStateStr, cmd);

    if (!isCmdSuccess)
    {
        ABC_LOG_ERR("Failed to get the charging state, returning default (%s)",
                    s_DEFAULT_CHARGING_STATE ? chargingStr : dischargingStr);

        return s_DEFAULT_CHARGING_STATE;
    }

    // Truncate the string if overflown.
    batteryStateStr[bufferLen - 1] = '\0';

    // Remove the newline from the end of the string.
    batteryStateStr[strlen(batteryStateStr) - 1] = '\0';

    const bool isCharging = (0 == strcmp(chargingStr, batteryStateStr));

    ABC_LOG("isCharging = %u, battery state = `%s`", isCharging, batteryStateStr);

    return isCharging;
}
