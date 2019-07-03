#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

void fake_abc_terminalController_setMaxBrightness(uint16_t value);

uint16_t fake_abc_terminalController_getCurrentBrightness(void);

void
fake_abc_terminalController_failRead(bool isFailed);

unsigned
fake_abc_terminalController_getNumWrites(void);

void
fake_abc_terminalController_resetNumWriteCalls(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
