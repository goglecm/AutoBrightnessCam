#include "abc_terminal_controller/abc_terminal_controller.h"
#include "abc_backlight_brightness_controller/fake_abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

static uint16_t
s_currentBrightness;

static bool
s_isCurrentBrightnessSet = false;

static unsigned
s_numWriteCalls;

bool
abc_terminalController_writeFile(int value, const char *pFileName)
{
    if (NULL == pFileName)
    {
        return false;
    }

    ++s_numWriteCalls;

    s_currentBrightness = value;

    s_isCurrentBrightnessSet = true;

    return true;
}

uint16_t fake_abc_terminalController_getCurrentBrightness(void)
{
    if (!s_isCurrentBrightnessSet)
    {
        ABC_LOG_ERR("current brightness not set");

        assert(false);
    }

    return s_currentBrightness;
}

unsigned
fake_abc_terminalController_getNumWrites(void)
{
    return s_numWriteCalls;
}

void
fake_abc_terminalController_resetNumWriteCalls(void)
{
    s_numWriteCalls = 0;
}
