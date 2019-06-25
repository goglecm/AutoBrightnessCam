#include "abc_ambient_brightness_controller.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

double abc_ambientBrightnessController_get(void)
{
    const char cmdCamera[] = "fswebcam --no-banner -r 160x120 --jpeg 50 /tmp/brightness.jpg";

    if (system(cmdCamera))
    {
        assert(false);
    }

    const char cmdBrightness[] = "convert /tmp/brightness.jpg -colorspace gray -format %[fx:100*mean]%% info:";

    FILE *pProcessOut_file = popen(cmdBrightness, "r");

    assert(pProcessOut_file);

    char brightness[10] = { 0 };

    if (NULL == fgets(brightness, sizeof(brightness), pProcessOut_file))
    {
        assert(false);
    }

    if (pclose(pProcessOut_file))
    {
        assert(false);
    }

    const double ambientBrightness = strtod(brightness, NULL);

    assert(ambientBrightness);

    return ambientBrightness;
}
