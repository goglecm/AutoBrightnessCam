#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void fake_abc_terminalController_setMaxBrightness(uint16_t value);

uint16_t fake_abc_terminalController_getCurrentBrightness(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
