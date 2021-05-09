#include "abc_config_service_common.h"

#include "abc_logging_service/abc_logging_service.h"

#include <libconfig.h>
#include <assert.h>
#include <string.h>


// Parser implementation using libconfig,

bool
readKeyValue(
        const abc_Key_t key,
        int *const restrict pValue,
        const char *const restrict pFileName)
{
    assert(isKeyValid(key) && !isKeyStr(key) && pValue && pFileName);

    config_t c;

    config_init(&c);

    int value;
    int status = config_read_file(&c, pFileName);
    if (status != CONFIG_TRUE)
    {
        goto done_fail;
    }

    status = config_lookup_int(&c, keyToStr(key), &value);
    if (status != CONFIG_TRUE)
    {
        goto done_fail;
    }


    *pValue = value;
    goto done_ok;


done_fail:

    ABC_LOG_ERR("Failed to read file %s at line %d: %s",
            config_error_file(&c),
            config_error_line(&c),
            config_error_text(&c));

done_ok:

    config_destroy ( &c );

    return status == CONFIG_TRUE;
}

bool
readKeyValueStr(
        const abc_Key_t key,
        char *const restrict pValue,
        const unsigned maxBufLen,
        const char *const restrict pFileName)
{
    assert(isKeyValid(key) && isKeyStr(key) && pValue && pFileName);

    config_t c;

    config_init(&c);

    const char *pConfigVal;
    int status = config_read_file(&c, pFileName);
    if (status != CONFIG_TRUE)
    {
        goto done_fail;
    }

    status = config_lookup_string(&c, keyToStr(key), &pConfigVal);
    if (status != CONFIG_TRUE)
    {
        goto done_fail;
    }

    if (strlen(pConfigVal) >= maxBufLen)
    {
        goto done_fail;
    }

    strcpy(pValue, pConfigVal);

    goto done_ok;


done_fail:

    ABC_LOG_ERR("Failed to read file %s at line %d: %s",
            config_error_file(&c),
            config_error_line(&c),
            config_error_text(&c));

done_ok:

    config_destroy ( &c );

    return status == CONFIG_TRUE;
}
