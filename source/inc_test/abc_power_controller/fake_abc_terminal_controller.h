#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void
fake_abc_terminalController_setUpowerState(bool isCharging);

bool
fake_abc_terminalController_calledUpower(void);

#ifdef __cplusplus
}
#endif


#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
