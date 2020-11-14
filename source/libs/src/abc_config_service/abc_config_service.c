#include "abc_config_service/abc_config_service.h"
#include "abc_config_service_common.h"

#include "abc_logging_service/abc_logging_service.h"
#include "abc_utils/abc_utils.h"
#include "abc_terminal_controller/abc_terminal_controller.h"

#include <stddef.h>


#ifndef ABC_HAS_LIBCONFIG

#error "ABC_HAS_LIBCONFIG not defined."

#endif // ABC_HAS_LIBCONFIG


// # Host configuration.
#ifndef ABC_CONFIG_DEFAULTS_FILENAME

#error "ABC_CONFIG_DEFAULTS_FILENAME not defined."

#endif // ABC_CONFIG_DEFAULTS_FILENAME


// # Default configuration.
#ifndef ABC_CONFIG_FILENAME

#error "ABC_CONFIG_FILENAME not defined."

#endif // ABC_CONFIG_FILENAME


bool
abc_configService_get(const abc_Key_t key, int *const restrict pValue)
{
    if (NULL == pValue)
    {
        ABC_LOG_ERR("Bad value return pointer");

        return false;
    }

    if (!isKeyValid(key))
    {
        ABC_LOG_ERR("Bad key %d", key);

        return false;
    }

    ABC_LOG("reading key `%s`", keyToStr(key));

    // Try to read from the host file.
    const bool isHostValueRead = readKeyValue(key, pValue, ABC_CONFIG_FILENAME);

    // If reading from host file fails, try reading from the defaults file.
    if (!isHostValueRead)
    {
        if (!readKeyValue(key, pValue, ABC_CONFIG_DEFAULTS_FILENAME))
        {
            ABC_LOG_ERR("Can't read key %d", key);

            return false;
        }
    }

    ABC_LOG("Setting key `%s` to %d read from `%s` file",
            keyToStr(key), *pValue, isHostValueRead ? "host" : "defaults");

    return true;
}
