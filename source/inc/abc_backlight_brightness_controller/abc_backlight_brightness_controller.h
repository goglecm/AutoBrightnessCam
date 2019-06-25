#ifndef AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

extern const double g_abc_BacklightBrightnessController_MAX;

extern const double g_abc_BacklightBrightnessController_MIN;

void abc_backlightBrightnessController_set(double value);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_H
