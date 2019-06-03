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

/*******************************
 * Global function definitions *
 *******************************/

void
abc_setBrightness(const abc_DisplayBrightnessInfo_t *const pDisplayInfo,
                  const double brightnessValue)
{
    // Read maximum brightness.
    FILE *const pMaxDisplayBrightnessFile = fopen(pDisplayInfo->pMaxDisplayBrightnessPath, "r");

    uint16_t maxBrightness = 0;

    (void)fscanf(pMaxDisplayBrightnessFile, "%"SCNu16, &maxBrightness);

    fclose(pMaxDisplayBrightnessFile);

    // Set new brightness.
    FILE *const pDisplayBrightnessFile = fopen(pDisplayInfo->pDisplayBrightnessPath, "w");

    (void)fprintf(pDisplayBrightnessFile, "%"PRIu16, (uint16_t)((brightnessValue / 100.0) * maxBrightness));

    fclose(pMaxDisplayBrightnessFile);
}
