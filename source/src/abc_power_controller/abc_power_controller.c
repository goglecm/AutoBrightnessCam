#include "abc_power_controller/abc_power_controller.h"

#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

bool
abc_powerController_isCharging(void)
{
    const char cmd[] = "upower -i `upower -e | "
                       "grep 'BAT'` | "
                       "grep state | "
                       "sed 's^state:^^g' | "
                       "sed 's^ ^^g'";

    char batteryStateStr[16] = { 0 };

    const bool result =
        abc_terminalController_sendReturnStr(sizeof(batteryStateStr),
                                             batteryStateStr,
                                             cmd);

    assert(result);

    // Remove the newline from the end of the string.
    batteryStateStr[strlen(batteryStateStr) - 1] = '\0';

    ABC_LOG("battery state = `%s`", batteryStateStr);

    return (0 == strcmp("charging", batteryStateStr));
}
