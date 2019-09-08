#ifndef AUTOBRIGHTNESSCAM_ABC_AMBIENT_BRIGHTNESS_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_ABC_AMBIENT_BRIGHTNESS_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool
abc_ambientBrightnessController_get(double *pBrightness);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_AMBIENT_BRIGHTNESS_CONTROLLER_H
