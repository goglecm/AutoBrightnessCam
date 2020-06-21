#include "abc_brightness_service/abc_brightness_service.h"
#include "abc_backlight_controller/abc_backlight_controller.h"
#include "abc_config_service/abc_config_service.h"
#include "abc_logging_service/abc_logging_service.h"

#include <stdlib.h>
#include <argp.h>
#include <unistd.h>

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <config.h>

#endif // #ifndef CONFIG_H_INCLUDED


const char *argp_program_version     = PACKAGE_STRING;
const char *argp_program_bug_address = "<" PACKAGE_BUGREPORT ">";

static const char doc[] =
    "App to automatically adjust the display brightness using the luminosity "
    "information from the webcam. To start it, simply pass no arguments.";

static struct argp argp = { .doc = doc };

static void configure(void)
{
    // Set the sampling period.
    int samplingPeriod;
    const bool isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD,
                &samplingPeriod);

    if (isResultOK)
    {
        abc_brightnessService_setPeriod(samplingPeriod);
    }
    else
    {
        ABC_LOG_ERR("Couldn't read sampling period");
        exit(-1);
    }

    // Set the brightness change speed.
    abc_backlightBrightnessController_setIncrementsPeriod_ms(50);
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        // Displaying help.

        argp_parse(&argp, argc, argv, 0, 0, 0);

        exit(0);
    }

    // Get on with the main app.

    configure();

    abc_brightnessService_start();

    do
    {
        // Wake up every second to check if we need to take a picture.
        sleep(1);
    }
    while (abc_brightnessService_wakeUp() == ABC_BRIGHTNESSSERVICE_SUCCESS);

    return -1;
}
