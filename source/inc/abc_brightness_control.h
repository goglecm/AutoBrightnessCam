#ifndef AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CONTROL_H
#define AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/**************
 * Structures *
 **************/

typedef struct
{
    const char *pDisplayBrightnessPath;

    const char *pMaxDisplayBrightnessPath;

} abc_DisplayBrightnessInfo_t;

/*************************
 * Function declarations *
 *************************/

void
abc_setBrightness(const abc_DisplayBrightnessInfo_t *pDisplayInfo,
                  double brightnessValue);

void
abc_getBrightness(const abc_DisplayBrightnessInfo_t *pDisplayInfo,
                  double *pBrightnessValue);

#ifdef __cplusplus
} // end extern "C"
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_CONTROL_H
