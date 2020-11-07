#ifndef AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <stdbool.h>

void
abc_backlightBrightnessController_set(double value);


// Set and get min/max brightness (in %).
bool
abc_backlightBrightnessController_setMinMax(int minBrightness, int maxBrightness);

double
abc_backlightBrightnessController_getMax(void);

double
abc_backlightBrightnessController_getMin(void);


// Function to set the path where the max brightness can be read.
void
abc_backlightBrightnessController_setMaxPath(const char *pPath);

// Function to set the path where the current brightness can be set/read.
void
abc_backlightBrightnessController_setCurrentPath(const char *pPath);

// Function to reset the current max brightness value.
// Used when the maximum brightness has changed.
void
abc_backlightBrightnessController_resetMax(void);

bool
abc_backlightBrightnessController_setNumIncrements(unsigned num);

void
abc_backlightBrightnessController_setIncrementsPeriod_ms(unsigned period_ms);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H
