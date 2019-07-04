#include "abc_ambient_brightness_controller/abc_ambient_brightness_controller.h"
#include "abc_terminal_controller/abc_terminal_controller.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_BUFF_SIZE 128

static const char
s_PICTURE_PATH[] = "/tmp/brightness.jpg";

static void
takePicture_fswebcam(const char *const restrict pPicPath)
{
    const char s[] = "fswebcam --no-banner -r 160x120 --jpeg 50 %s";

    char cmdCamera[MAX_BUFF_SIZE] = { 0 };

    if (0 >= snprintf(cmdCamera, sizeof(cmdCamera), s, pPicPath))
    {
        assert(false);
    }

    const bool result = abc_terminalController_send(cmdCamera);

    assert(result);
}

static double
getBrightnessFromPicture_convert(const char *const restrict pPicPath)
{
    const char s[] = "convert %s "
                     "-colorspace gray "
                     "-format %%[fx:100*mean]%%%% info:";

    char cmdBrightness[MAX_BUFF_SIZE] = { 0 };

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

bool
abc_ambientBrightnessController_get(double *const restrict pResult)
{
    takePicture_fswebcam(s_PICTURE_PATH);

    if (pResult)
    {
        *pResult = getBrightnessFromPicture_convert(s_PICTURE_PATH);
    }
    else
    {
        return false;
    }

    return true;
}
