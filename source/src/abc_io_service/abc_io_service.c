#include "abc_io_service/abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

bool
abc_ioService_write(int value, const char *pFileName)
{
    if (NULL == pFileName)
    {
        ABC_LOG_ERR("Invalid filename");

        return false;
    }

    errno = 0;

    FILE *pFile = fopen(pFileName, "w");

    if (NULL == pFile)
    {
        ABC_LOG_ERR("Failed to open the file `%s` due to: %s",
                    pFileName, strerror(errno));

        return false;
    }

    bool isReturnOK = true;

    const int numWrittenBytes = fprintf(pFile, "%d", value);

    if (numWrittenBytes < 0)
    {
        ABC_LOG_ERR("Failed to write to file `%s` due to: %s",
                    pFileName, strerror(errno));

        isReturnOK = false;
    }
    else if (numWrittenBytes == 0)
    {
        ABC_LOG_ERR("Nothing written to the file `%s` due to: %s",
                    pFileName, strerror(errno));

        isReturnOK = false;
    }
    else
    {
        ABC_LOG("Written %d to file `%s`", value, pFileName);
    }

    errno = 0;

    if (0 != fclose(pFile))
    {
        ABC_LOG_ERR("Failed to close file `%s` due to: %s. "
                    "File is left in an undefined state.",
                    pFileName, strerror(errno));

        return false;
    }

    return isReturnOK;
}

bool
abc_ioService_read(int *pValue, const char *pFileName)
{
    (void)pValue;
    (void)pFileName;
    return true;
}

#if 0


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


#endif