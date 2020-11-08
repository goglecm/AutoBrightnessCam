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

#define FATAL_ERROR(...)  do {   \
    ABC_LOG_ERR(__VA_ARGS__);    \
    ABC_LOG_STDERR(__VA_ARGS__); \
    exit(-1);                    \
} while (0)


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
        FATAL_ERROR("Couldn't read sampling period");
    }

    // Set the transition smoothness and speed.
    int transitionSmoothness;
    isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_TRANSITION_SMOOTHNESS,
                &transitionSmoothness);

    if (!isResultOK)
    {
        FATAL_ERROR("Couldn't read transition smoothness");
    }

    const int minSmoothnessLevel = 1;
    const int maxSmoothnessLevel = 10;
    if (transitionSmoothness < minSmoothnessLevel ||
        transitionSmoothness > maxSmoothnessLevel)
    {
        FATAL_ERROR("Out of range transition smoothness");
    }

    int transitionPeriod;
    isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_TRANSITION_PERIOD,
                &transitionPeriod);

    if (!isResultOK)
    {
        FATAL_ERROR("Couldn't read transition period");
    }

    if (transitionPeriod < 10 || transitionPeriod > 2000)
    {
        FATAL_ERROR("Out of range transition period %d. Allowed range: 10..2000.",
                transitionPeriod);
    }

    if (transitionPeriod > samplingPeriod * 1000)
    {
        FATAL_ERROR("Transition period %d ms cannot exceed sampling period %d ms",
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

    // Set the min/max brightness.
    int minBrightness;
    isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_MIN_BRIGHTNESS,
                &minBrightness);

    if (!isResultOK)
    {
        FATAL_ERROR("Couldn't read min brightness");
    }

    int maxBrightness;
    isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_MAX_BRIGHTNESS,
                &maxBrightness);

    if (!isResultOK)
    {
        FATAL_ERROR("Couldn't read max brightness");
    }

    isResultOK =
        abc_backlightBrightnessController_setMinMax(minBrightness, maxBrightness);

    if (!isResultOK)
    {
        FATAL_ERROR("Bad min/max brightness [%d..%d]", minBrightness, maxBrightness);
    }

    // Check if we want to depend of battery or not.
    int dependOnBattery;
    isResultOK =
        abc_configService_get(
                ABC_CONFIG_SERVICE_KEY_DEPEND_ON_BATTERY,
                &dependOnBattery);

    if (!isResultOK)
    {
        FATAL_ERROR("Couldn't check if we depend on battery");
    }

    if (dependOnBattery != 0 && dependOnBattery != 1)
    {
        FATAL_ERROR("Out of range dependOnBattery [0..1], got %d", dependOnBattery);
    }

    abc_brightnessService_ignoreBattery(!dependOnBattery);
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

    FATAL_ERROR("The wake up function failed");
}
