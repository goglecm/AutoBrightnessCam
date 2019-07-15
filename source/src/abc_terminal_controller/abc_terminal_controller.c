#include "abc_terminal_controller/abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

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
    int errCode = 0;
    bool result = true;

    if (resultLen > 0 && pResult)
    {
        // use popen
        FILE *const restrict pProcessOut_file = popen(pCmd, "r");

        if (NULL == pProcessOut_file)
        {
            ABC_LOG_ERR("Returning false: Failed to run cmd `%s` due to `%s`",
                        pCmd ? pCmd : "bad command", strerror(errno));

            return false;
        }

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

            result = false;
        }
    }
    else
    {
        // use system
        errCode = system(pCmd);

        if (errCode)
        {
            result = false;

            ABC_LOG_ERR("Returning false: Failed to run cmd `%s` due to %d",
                        pCmd ? pCmd : "bad command", errCode);
        }
    }

    return result;
}

bool
abc_terminalController_writeFile(const int value,
                                 const char *const restrict pFileName)
{
    if (NULL == pFileName)
    {
        ABC_LOG_ERR("Invalid filename");

        return false;
    }

    ABC_LOG("writing %d to %s", value, pFileName);

    char cmd[MAX_BUFF_SIZE] = { 0 };

    int result;
    result = snprintf(cmd, sizeof(cmd), "echo %"PRId32" > %s", value, pFileName);

    if (result <= 0)
    {
        ABC_LOG_ERR("Returning false: Failed to construct the cmd to write the file");

        return false;
    }

    if (!abc_terminalController_sendReturnStr(0, NULL, cmd))
    {
        return false;
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

        ABC_LOG("return value = %f", *pValue);
    }

    return true;
}
