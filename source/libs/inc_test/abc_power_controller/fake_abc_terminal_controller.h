#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "abc_power_controller/abc_power_controller.h"

void
fake_abc_terminalController_setUpowerState(abc_powerController_State_t state);

bool
fake_abc_terminalController_calledUpower(void);

void
fake_abc_terminalController_resetStates(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
