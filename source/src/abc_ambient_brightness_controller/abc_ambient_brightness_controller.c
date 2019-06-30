#include "abc_ambient_brightness_controller.h"

#include "abc_terminal_controller.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static void
takePicture_fswebcam(const char *const restrict pPicPath)
{
    const char s[] = "fswebcam --no-banner -r 160x120 --jpeg 50 %s";

    char cmdCamera[128] = { 0 };

    if (0 >= snprintf(cmdCamera, sizeof(cmdCamera), s, pPicPath))
    {
        assert(false);
    }

    const bool result = abc_terminalController_sendReturnStr(0, NULL, cmdCamera);

    assert(result);
}

static double
getBrightnessFromPicture_convert(const char *const restrict pPicPath)
{
    const char s[] = "convert %s "
                     "-colorspace gray "
                     "-format %%[fx:100*mean]%%%% info:";

    char cmdBrightness[128] = { 0 };

    if (0 >= snprintf(cmdBrightness, sizeof(cmdBrightness), s, pPicPath))
    {
        assert(false);
    }

    double ambientBrightness;

    const bool result =
        abc_terminalController_sendReturnDbl(&ambientBrightness, cmdBrightness);

    assert(result);

    return ambientBrightness;
}

double
abc_ambientBrightnessController_get(void)
{
    const char picPath[] = "/tmp/brightness.jpg";

    takePicture_fswebcam(picPath);

    return getBrightnessFromPicture_convert(picPath);
}
