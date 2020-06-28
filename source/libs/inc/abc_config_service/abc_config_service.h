#ifndef AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum
{
    ABC_CONFIG_SERVICE_KEY_UNKNOWN,
    ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD, // Secs to the next picture.
    ABC_CONFIG_SERVICE_KEY_TRANSITION_SMOOTHNESS, // 1 not smooth, 10 very smooth.
    ABC_CONFIG_SERVICE_KEY_TRANSITION_PERIOD, // 10 to 2000 ms.
} abc_configService_Key_t;

bool
abc_configService_get(abc_configService_Key_t key, int *pValue);

#ifdef __cplusplus
}
#endif

#endif // AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_H
