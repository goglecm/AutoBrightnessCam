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
    bool isResultOK =
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

    // Set the transition smoothness and speed.
    int transitionSmoothness;
    isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_TRANSITION_SMOOTHNESS,
                &transitionSmoothness);

    if (!isResultOK)
    {
        ABC_LOG_ERR("Couldn't read transition smoothness");
        exit(-1);
    }

    const int minSmoothnessLevel = 1;
    const int maxSmoothnessLevel = 10;
    if (transitionSmoothness < minSmoothnessLevel ||
        transitionSmoothness > maxSmoothnessLevel)
    {
        ABC_LOG_ERR("Out of range transition smoothness");
        exit(-1);
    }

    int transitionPeriod;
    isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_TRANSITION_PERIOD,
                &transitionPeriod);

    if (!isResultOK)
    {
        ABC_LOG_ERR("Couldn't read transition period %d", transitionSmoothness);
        exit(-1);
    }

    if (transitionPeriod < 10 || transitionPeriod > 2000)
    {
        ABC_LOG_ERR("Out of range transition period %d", transitionPeriod);
        exit(-1);
    }

    if (transitionPeriod > samplingPeriod * 1000)
    {
        ABC_LOG_ERR("Transition period %d ms cannot exceed sampling period %d ms",
                transitionPeriod, samplingPeriod * 1000);
    }

    // A smooth transition occurs at 1 brightness change per 10 ms.
    // A rough transition occurs at 1 brightness change per 500 ms.
    static const int minTransPeriod = 10;
    static const int maxTransPeriod = 500;
    static const int numSmoothnessLevels = maxSmoothnessLevel - minSmoothnessLevel;
    static const int incrementPeriodPerLevel =
        (maxTransPeriod - minTransPeriod) / numSmoothnessLevels;

    const int effectiveIncrementPeriod =
        minTransPeriod +
        incrementPeriodPerLevel * (maxSmoothnessLevel - transitionSmoothness);

    const int numIncrements = transitionPeriod / effectiveIncrementPeriod;

    ABC_LOG("Increment period set to %d ms, num increments %d over %d ms",
            effectiveIncrementPeriod, numIncrements, transitionPeriod);

    abc_backlightBrightnessController_setIncrementsPeriod_ms(effectiveIncrementPeriod);
    abc_backlightBrightnessController_setNumIncrements(numIncrements);
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
