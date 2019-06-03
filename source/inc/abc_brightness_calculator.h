#ifndef AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CALCULATOR_H
#define AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/******************
 * Local includes *
 ******************/

#include "abc_common.h"

/*************************
 * Variable declarations *
 *************************/

extern const abc_Percentage_t g_abc_MIN_BRIGHTNESS;
extern const abc_Percentage_t g_abc_MAX_BRIGHTNESS;

/*************************
 * Function declarations *
 *************************/

abc_Percentage_t
abc_calculateNewBrightness(abc_Percentage_t ambientBrightness);

#ifdef __cplusplus
} // end extern "C"
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CALCULATOR_H
