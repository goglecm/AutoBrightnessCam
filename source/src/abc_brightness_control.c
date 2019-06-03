/****************
 * Main include *
 ****************/

#include "abc_brightness_control.h"

/*********************
 * Standard includes *
 *********************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/************
 * Typedefs *
 ************/

typedef uint16_t RawValue_t; // 0.0 - 100.0 %

/*******************************
 * Local function definitions *
 *******************************/

static RawValue_t
readBrightness(const char brightnessDevicePath[])
{
    FILE *const pBrightnessDeviceFile = fopen(brightnessDevicePath, "r");

    RawValue_t value = 0;

    fscanf(pBrightnessDeviceFile, "%"SCNu16, &value);

    fclose(pBrightnessDeviceFile);

    return value;
}

static void
writeBrightness(const char brightnessDevicePath[], const RawValue_t value)
{
    FILE *const pBrightnessDeviceFile = fopen(brightnessDevicePath, "w");

    (void)fprintf(pBrightnessDeviceFile, "%"PRIu16, value);

    fclose(pBrightnessDeviceFile);
}

static double
normalise(const abc_Percentage_t value)
{
    // Convert percentages to equivalent fractions, i.e. 70% -> 0.7
    return value / 100.0;
}

/*******************************
 * Global function definitions *
 *******************************/

void
abc_setBrightness(const abc_BrightnessDeviceInfo_t *const pInfo,
                  const abc_Percentage_t value)
{
    const RawValue_t rawValue = normalise(value) * readBrightness(pInfo->pMax);

    writeBrightness(pInfo->pCurrent, rawValue);
}
