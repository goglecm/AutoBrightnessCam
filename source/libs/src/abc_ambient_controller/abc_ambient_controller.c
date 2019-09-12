#include "abc_ambient_controller/abc_ambient_controller.h"
#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdbool.h>
#include <stdio.h>

#define MAX_BUFF_SIZE 128

bool
abc_ambientBrightnessController_get(double *const restrict pResult)
{
    if (NULL == pResult)
    {
        ABC_LOG_ERR("bad parameter");

        return false;
    }

    static char fullCmd[MAX_BUFF_SIZE];

    fullCmd[MAX_BUFF_SIZE - 1] = '\0';

    static const char cameraCmd[] = "fswebcam --no-banner -r 160x120 --jpeg 50";

    static const char picPath[] = "/tmp/brightness.jpg";

    if (0 >= snprintf(fullCmd, sizeof(fullCmd), "%s %s", cameraCmd, picPath))
    {
        ABC_LOG_ERR("failed to format camera cmd");

        return false;
    }

    if (!abc_terminalController_send(fullCmd))
    {
        ABC_LOG_ERR("failed to execute cmd which takes a picture");

        return false;
    }

    static const char convertCmd[] = "convert %s "
                                     "-colorspace gray "
                                     "-format %%[fx:100*mean]%%%% info:";

    if (0 >= snprintf(fullCmd, sizeof(fullCmd), convertCmd, picPath))
    {
        ABC_LOG_ERR("failed to construct convert cmd");

        return false;
    }

    double ambientBrightness;
    if (!abc_terminalController_sendReturnDbl(&ambientBrightness, fullCmd))
    {
        ABC_LOG_ERR("failed to get brightness from picture");

        return false;
    }

    *pResult = ambientBrightness * 2;

    return true;
}
