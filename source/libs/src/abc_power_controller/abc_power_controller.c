#include "abc_power_controller/abc_power_controller.h"

#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 32U

bool
abc_powerController_isCharging(void)
{
    // todo: read /sys/class/power_supply/BAT1/status

    static const char cmd[] = "upower -i `upower -e | "
                              "fgrep 'BAT'` | "
                              "fgrep state | "
                              "sed 's^state:^^g' | "
                              "sed 's^ ^^g'";

    static const char chargingStr[] = "charging";
    static const char dischargingStr[] = "discharging";
    static const char fullyChargedStr[] = "fully-charged";

    char batteryStateStr[BUFF_SIZE];

    if (!abc_terminalController_sendReturnStr(BUFF_SIZE, batteryStateStr, cmd))
    {
        ABC_LOG_ERR("Failed to get the charging state, returning default (%s)",
                    dischargingStr);

        return false;
    }

    // Truncate the string if overflown.
    batteryStateStr[BUFF_SIZE - 1] = '\0';

    // Remove the newline from the end of the string.
    batteryStateStr[strlen(batteryStateStr) - 1] = '\0';

    const bool isCharging = (0 == strcmp(chargingStr, batteryStateStr)) ||
                            (0 == strcmp(fullyChargedStr, batteryStateStr));

    ABC_LOG("isCharging = %u, battery state = `%s`", isCharging, batteryStateStr);

    return isCharging;
}
