#ifndef AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <stdbool.h>

extern const double
g_abc_BacklightBrightnessController_MAX;

extern const double
g_abc_BacklightBrightnessController_MIN;

void
abc_backlightBrightnessController_set(double value);

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
