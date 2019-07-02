#include "abc_power_controller/abc_power_controller.h"

#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#define BUFF_SIZE 32U

static const bool s_DEFAULT_CHARGING_STATE = false;

bool
abc_powerController_isCharging(void)
{
    const char cmd[] = "upower -i `upower -e | "
                       "grep 'BAT'` | "
                       "grep state | "
                       "sed 's^state:^^g' | "
                       "sed 's^ ^^g'";

    char batteryStateStr[BUFF_SIZE] = {0};

    const bool result =
        abc_terminalController_sendReturnStr(sizeof(batteryStateStr),
                                             batteryStateStr,
                                             cmd);

    if (!result)
    {
        ABC_LOG("Failed to get the charging state, returning default (%s)",
                (s_DEFAULT_CHARGING_STATE ? "charging" : "discharging"));

        return s_DEFAULT_CHARGING_STATE;
    }

    // Truncate the string if overflown.
    batteryStateStr[sizeof(batteryStateStr) - 1] = '\0';

    // Remove the newline from the end of the string.
    batteryStateStr[strlen(batteryStateStr) - 1] = '\0';

    ABC_LOG("battery state = `%s`", batteryStateStr);

    return (0 == strcmp("charging", batteryStateStr));
}
