#ifndef AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum
{
    ABC_CONFIG_SERVICE_KEY_UNKNOWN,
    ABC_CONFIG_SERVICE_KEY__FIRST,
    ABC_CONFIG_SERVICE_KEY_DEPEND_ON_BATTERY = ABC_CONFIG_SERVICE_KEY__FIRST, // 1 or 0.
    ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD, // Secs to the next picture.
    ABC_CONFIG_SERVICE_KEY_TRANSITION_SMOOTHNESS, // 1 not smooth, 10 very smooth.
    ABC_CONFIG_SERVICE_KEY_TRANSITION_PERIOD, // 10 to 2000 ms.
    ABC_CONFIG_SERVICE_KEY_MIN_BRIGHTNESS, // 0..100%
    ABC_CONFIG_SERVICE_KEY_MAX_BRIGHTNESS, // 0..100%
    ABC_CONFIG_SERVICE_KEY_BRIGHTNESS_FILE, // Current brightness.
    ABC_CONFIG_SERVICE_KEY_MAX_BRIGHTNESS_FILE, // Max brightness.
    ABC_CONFIG_SERVICE_KEY_BATTERY_FILES, // Battery locations.
    ABC_CONFIG_SERVICE_KEY__LAST = ABC_CONFIG_SERVICE_KEY_BATTERY_FILES,
} abc_configService_Key_t;

bool
abc_configService_getStrElem(
        abc_configService_Key_t key,
        char *pValue,
        unsigned maxBufLen,
        unsigned idx);

bool
abc_configService_getStr(abc_configService_Key_t key, char *pValue, unsigned maxBufLen);

bool
abc_configService_get(abc_configService_Key_t key, int *pValue);

#ifdef __cplusplus
}
#endif

#endif // AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_H
