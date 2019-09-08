#include "abc_terminal_controller/abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_BUFF_SIZE 128U

bool
abc_terminalController_send(const char *const restrict pCmd)
{
    // use system
    const int errCode = system(pCmd);
    if (errCode)
    {
        ABC_LOG_ERR("Returning false: Failed to run cmd `%s` due to %d",
                    pCmd ? pCmd : "bad command", errCode);

        return false;
    }

    return true;
}

bool
abc_terminalController_sendReturnStr(const unsigned resultLen,
                                     char *const restrict pResult,
                                     const char *const restrict pCmd)
{
    if (pResult == NULL || resultLen == 0)
    {
        return false;
    }

    FILE *const restrict pProcessOut_file = popen(pCmd, "r");

    if (NULL == pProcessOut_file)
    {
        ABC_LOG_ERR("Returning false: Failed to run cmd `%s` due to `%s`",
                    pCmd ? pCmd : "bad command", strerror(errno));

        return false;
    }

    int errCode = 0;
    bool result = true;

    if (NULL == fgets(pResult, resultLen, pProcessOut_file))
    {
        clearerr(pProcessOut_file);
        errCode = ferror(pProcessOut_file);

        ABC_LOG_ERR("Will return false: Failed to read file due to %d", errCode);

        result = false;
    }
    else
    {
        ABC_LOG("pResult = `%s`", pResult);
    }

    errCode = pclose(pProcessOut_file);
    if (errCode)
    {
        ABC_LOG_ERR("Will return false: Failed to finish cmd due to %d", errCode);

        return false;
    }

    return result;
}

bool
abc_terminalController_sendReturnDbl(double *const restrict pValue,
                                     const char *const restrict pCmd)
{
    if (pValue)
    {
        char strValue[MAX_BUFF_SIZE];

        if (!abc_terminalController_sendReturnStr(MAX_BUFF_SIZE, strValue, pCmd))
        {
            return false;
        }

        strValue[MAX_BUFF_SIZE - 1] = '\0';
        *pValue = strtod(strValue, NULL);

        ABC_LOG("return value = %f", *pValue);
    }
    else
    {
        if (!abc_terminalController_send(pCmd))
        {
            return false;
        }
    }

    return true;
}
