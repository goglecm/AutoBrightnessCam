#include "abc_terminal_controller/abc_terminal_controller.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_BUFF_SIZE 128U

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
    if (resultLen > 0 && pResult)
    {
        // use popen

        FILE *const pProcessOut_file = popen(pCmd, "r");

        if (NULL == pProcessOut_file)
        {
            return false;
        }

        bool result = true;

        if (NULL == fgets(pResult, resultLen, pProcessOut_file))
        {
            result = false;
        }

        if (pclose(pProcessOut_file))
        {
            return false;
        }

        return result;
    }
    else
    {
        // use system
        return (system(pCmd) == 0);
    }
}

bool
abc_terminalController_writeFile(const int value,
                                 const char *const restrict pFileName)
{
    if (NULL == pFileName)
    {
        return true;
    }

    char cmd[MAX_BUFF_SIZE] = { 0 };

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
    if (NULL == pFileName)
    {
        return true;
    }

    char cmd[MAX_BUFF_SIZE] = { 0 };

    int result;
    result = snprintf(cmd, sizeof(cmd), "cat %s", pFileName);

    if (result <= 0)
    {
        return false;
    }

    char strValue[MAX_BUFF_SIZE] = { 0 };

    if (!abc_terminalController_sendReturnStr(sizeof(strValue), strValue, cmd))
    {
        return false;
    }

    if (pValue)
    {
        *pValue = strtoimax(strValue, NULL, 10);
    }

    return true;
}

bool
abc_terminalController_sendReturnDbl(double *const restrict pValue,
                                     const char *const restrict pCmd)
{
    char strValue[MAX_BUFF_SIZE] = { 0 };

    if (!abc_terminalController_sendReturnStr(sizeof(strValue), strValue, pCmd))
    {
        return false;
    }

    if (pValue)
    {
        *pValue = strtod(strValue, NULL);
    }

    return true;
}
