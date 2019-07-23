#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint16_t
fake_abc_terminalController_getNumShots(void);

void
fake_abc_terminalController_resetNumShots(void);

uint16_t
fake_abc_terminalController_getNumCalcs(void);

void
fake_abc_terminalController_resetNumCalcs(void);


#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
