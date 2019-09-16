#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "abc_power_controller/abc_power_controller.h"

void
fake_abc_ioService_setBatteryState(abc_powerController_State_t state);

bool
fake_abc_ioService_wasStateRead(void);

void
fake_abc_ioService_resetStates(void);

void
fake_abc_ioService_setBatteryStatePath(const char *pFileName);

#ifdef __cplusplus
}
#endif

#endif // #ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H
