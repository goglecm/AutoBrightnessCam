#include "abc_power_controller.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "abc_terminal_controller.h"

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

    return (0 == strcmp("charging", batteryStateStr));
}
