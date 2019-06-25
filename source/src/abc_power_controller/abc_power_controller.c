#include "abc_power_controller.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

bool
abc_powerController_isCharging(void)
{
    const char cmd[] = "upower -i `upower -e | grep 'BAT'` | "
                       "grep state | "
                       "sed 's^state:^^g' | "
                       "sed 's^ ^^g'";

    FILE *const pProcessOut_file = popen(cmd, "r");

    assert(pProcessOut_file);

    char batteryStateStr[16] = { 0 };
    if (NULL == fgets(batteryStateStr, sizeof(batteryStateStr), pProcessOut_file))
    {
        assert(false);
    }

    if (pclose(pProcessOut_file))
    {
        assert(false);
    }

    return (0 == strcmp("charging", batteryStateStr));
}
