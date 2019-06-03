#ifndef AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CONTROL_H
#define AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/******************
 * Local includes *
 ******************/

#include "abc_common.h"

/**************
 * Structures *
 **************/

typedef struct
{
    const char *pCurrent;

    const char *pMax;

} abc_BrightnessDeviceInfo_t;

/*************************
 * Function declarations *
 *************************/

void
abc_setBrightness(const abc_BrightnessDeviceInfo_t *pInfo,
                  abc_Percentage_t value);

#ifdef __cplusplus
} // end extern "C"
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CONTROL_H
