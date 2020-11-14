#ifndef AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_COMMON_H
#define AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif


#include "abc_config_service/abc_config_service.h" // Provides abc_configService_Key_t enum.

#include <stdbool.h>

#include <assert.h>
#include <stddef.h>


// A few helper functions to be used locally.

typedef abc_configService_Key_t abc_Key_t;

// This function has multiple implementations.
bool
readKeyValue(abc_Key_t key, int *pValue, const char *pFileName);


static inline bool
isKeyValid(const abc_Key_t key)
{
    return key >= ABC_CONFIG_SERVICE_KEY__FIRST &&
           key <= ABC_CONFIG_SERVICE_KEY__LAST;
}

static inline const char *
keyToStr(const abc_Key_t key)
{
    assert(isKeyValid(key));

    switch (key)
    {
        case ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD:
        {
            static const char keyStr[] = "sampling_period";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_TRANSITION_SMOOTHNESS:
        {
            static const char keyStr[] = "transition_smoothness";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_TRANSITION_PERIOD:
        {
            static const char keyStr[] = "transition_period";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_MAX_BRIGHTNESS:
        {
            static const char keyStr[] = "max_brightness";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_MIN_BRIGHTNESS:
        {
            static const char keyStr[] = "min_brightness";
            return keyStr;
        }

        case ABC_CONFIG_SERVICE_KEY_DEPEND_ON_BATTERY:
        {
            static const char keyStr[] = "depend_on_battery";
            return keyStr;
        }

        default:
            assert(false && "Bad key");
            return NULL;
    }
}

#ifdef __cplusplus
}
#endif

#endif // AUTOBRIGHTNESSCAM_ABC_CONFIG_SERVICE_COMMON_H
