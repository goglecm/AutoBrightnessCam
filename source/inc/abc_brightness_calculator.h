#ifndef AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CALCULATOR_H
#define AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/************
 * Typedefs *
 ************/

typedef double abc_Percentage_t; // 0.0 - 100.0 %

typedef uint16_t abc_Brightness_t; // anything integer up to 65k

/*************************
 * Variable declarations *
 *************************/

// Min/max brightness percentages.
extern const abc_Percentage_t g_abc_MIN_BRIGHTNESS;
extern const abc_Percentage_t g_abc_MAX_BRIGHTNESS;

/*************************
 * Function declarations *
 *************************/

abc_Percentage_t
abc_calculateNewBrightnessPercentage(abc_Percentage_t ambientBrightness);

#ifdef __cplusplus
} // end extern "C"
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CALCULATOR_H
