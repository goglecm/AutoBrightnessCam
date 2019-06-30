#include "abc_terminal_controller.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

bool
abc_terminalController_send(const char *const restrict pCmd)
{
    return abc_terminalController_sendReturnStr(0, NULL, pCmd);
}

bool
abc_terminalController_sendReturnStr(const unsigned resultLen,
                                     char *const restrict pResult,
                                     const char *const restrict pCmd)
{
    assert(pCmd);

    bool result = true;

    // use popen
    if (resultLen > 0 && pResult)
    {
        FILE *const pProcessOut_file = popen(pCmd, "r");

        assert(pProcessOut_file);

        if (NULL == fgets(pResult, resultLen, pProcessOut_file))
        {
            result = false;
        }

        if (pclose(pProcessOut_file))
        {
            result = false;
        }
    }
    else
    {
        // use system
        result = (system(pCmd) == 0);
    }

    return result;
}

bool
abc_terminalController_writeFile(const int value,
                                 const char *const restrict pFileName)
{
    assert(pFileName);

    char cmd[128] = { 0 };

    int result;
    result = snprintf(cmd, sizeof(cmd), "echo %"PRId32" > %s", value, pFileName);

    if (result <= 0)
    {
        return false;
    }

    if (!abc_terminalController_sendReturnStr(0, NULL, cmd))
    {
        return false;
    }

    return true;
}

bool
abc_terminalController_readFile(int *const restrict pValue,
                                const char *const restrict pFileName)
{
    assert(pValue);
    assert(pFileName);

    char cmd[128] = { 0 };

    int result;
    result = snprintf(cmd, sizeof(cmd), "cat %s", pFileName);

    if (result <= 0)
    {
        return false;
    }

    char strValue[10] = { 0 };

    if (!abc_terminalController_sendReturnStr(sizeof(strValue), strValue, cmd))
    {
        return false;
    }

    *pValue = strtoimax(strValue, NULL, 10);

    return true;
}

bool
abc_terminalController_sendReturnDbl(double *const restrict pValue,
                                     const char *const restrict pCmd)
{
    assert(pValue);
    assert(pCmd);

    char strValue[10] = { 0 };

    if (!abc_terminalController_sendReturnStr(sizeof(strValue), strValue, pCmd))
    {
        return false;
    }

    *pValue = strtod(strValue, NULL);

    return true;
}
