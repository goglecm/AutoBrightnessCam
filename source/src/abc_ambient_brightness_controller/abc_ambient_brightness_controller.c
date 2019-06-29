#include "abc_ambient_brightness_controller.h"

#include "abc_terminal_controller.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static void takePicture_fswebcam(const char *const restrict pPicPath)
{
    char cmdCamera[128] = { 0 };

    if (0 >= snprintf(cmdCamera, sizeof(cmdCamera), "fswebcam --no-banner -r 160x120 --jpeg 50 %s", pPicPath))
    {
        assert(false);
    }

    const bool result = abc_terminalController_send(0, NULL, cmdCamera);

    assert(result);
}

static double getBrightnessFromPicture_convert(const char *const restrict pPicPath)
{
    char cmdBrightness[128] = { 0 };

    if (0 >= snprintf(cmdBrightness, sizeof(cmdBrightness), "convert %s -colorspace gray -format %%[fx:100*mean]%%%% info:", pPicPath))
    {
        assert(false);
    }

    double ambientBrightness;

    const bool result =
        abc_terminalController_readCmdDouble(&ambientBrightness, cmdBrightness);

    assert(result);

    return ambientBrightness;
}

double abc_ambientBrightnessController_get(void)
{
    const char picPath[] = "/tmp/brightness.jpg";

    takePicture_fswebcam(picPath);

    return getBrightnessFromPicture_convert(picPath);
}
