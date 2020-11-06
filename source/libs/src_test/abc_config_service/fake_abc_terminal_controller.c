#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_config_service/fake_abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

#include <string.h>
#include <assert.h>
#include <stddef.h>

// NULL means the strings are not set.
typedef struct
{
    const char *pEntryCountStr;
    const char *pEntryValueStr;
    const char *pDefaultEntryCountStr;
    const char *pDefaultEntryValueStr;
}
ReturnStrings_t;

static ReturnStrings_t
s_returnStrings;

void
fake_abc_terminalController_setReturnStr(
        const char *const pRetVal,
        const bool isDefault,
        const bool isCount)
{
    assert(pRetVal);

    if (isDefault)
    {
        if (isCount)
        {
            s_returnStrings.pDefaultEntryCountStr = pRetVal;
        }
        else
        {
            s_returnStrings.pDefaultEntryValueStr = pRetVal;
        }
    }
    else
    {
        if (isCount)
        {
            s_returnStrings.pEntryCountStr = pRetVal;
        }
        else
        {
            s_returnStrings.pEntryValueStr = pRetVal;
        }
    }
}

bool
abc_terminalController_sendReturnStr(const unsigned resultLen,
                                     char *const restrict pResult,
                                     const char *const restrict pCmd)
{
    assert(resultLen);
    assert(pResult);
    assert(pCmd);

    // Return the next available string from the list of strings to return.
    // The order is important.
    if (s_returnStrings.pEntryCountStr)
    {
        assert(resultLen > strlen(s_returnStrings.pEntryCountStr));

        strcpy(pResult, s_returnStrings.pEntryCountStr);

        s_returnStrings.pEntryCountStr = NULL;
    }
    else if (s_returnStrings.pEntryValueStr)
    {
        assert(resultLen > strlen(s_returnStrings.pEntryValueStr));

        strcpy(pResult, s_returnStrings.pEntryValueStr);

        s_returnStrings.pEntryValueStr = NULL;
    }
    else if (s_returnStrings.pDefaultEntryCountStr)
    {
        assert(resultLen > strlen(s_returnStrings.pDefaultEntryCountStr));

        strcpy(pResult, s_returnStrings.pDefaultEntryCountStr);

        s_returnStrings.pDefaultEntryCountStr = NULL;
    }
    else if (s_returnStrings.pDefaultEntryValueStr)
    {
        assert(resultLen > strlen(s_returnStrings.pDefaultEntryValueStr));

        strcpy(pResult, s_returnStrings.pDefaultEntryValueStr);

        s_returnStrings.pDefaultEntryValueStr = NULL;
    }
    else
    {
        ABC_LOG_ERR("No more strings left to use");

        assert(false);
    }


    return true;
}
