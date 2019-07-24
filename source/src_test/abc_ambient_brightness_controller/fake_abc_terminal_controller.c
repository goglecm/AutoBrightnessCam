#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_ambient_brightness_controller/fake_abc_terminal_controller.h"

#include <string.h>
#include <assert.h>

static uint16_t
s_numShots;

static uint16_t
s_numCalcs;

uint16_t
fake_abc_terminalController_getNumShots(void)
{
    return s_numShots;
}

void
fake_abc_terminalController_resetNumShots(void)
{
    s_numShots = 0;
}

uint16_t
fake_abc_terminalController_getNumCalcs(void)
{
    return s_numShots;
}

void
fake_abc_terminalController_resetNumCalcs(void)
{
    s_numShots = 0;
}

bool
abc_terminalController_send(const char *pCmd)
{
    assert(pCmd);

    const char cameraCmd[] = "fswebcam";

    const size_t cmdSize = strnlen(cameraCmd, strlen(cameraCmd));

    if (0 == memcmp(cameraCmd, pCmd, cmdSize))
    {
        ++s_numShots;
    }

    return true;
}

bool
abc_terminalController_sendReturnDbl(double *const restrict pValue,
                                     const char *const restrict pCmd)
{
    assert(pCmd && pValue);

    const char calcCmd[] = "convert";

    const size_t cmdSize = strnlen(calcCmd, strlen(calcCmd));

    if (0 == memcmp(calcCmd, pCmd, cmdSize))
    {
        ++s_numCalcs;
    }

    *pValue = 10;

    return true;
}
