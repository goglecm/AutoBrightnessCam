#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum fake_abc_terminalController_ChargingState_t
{
    FAKE_ABC_TERMINAL_CONTROLLER_STATE_UNKNOWN,
    FAKE_ABC_TERMINAL_CONTROLLER_STATE_DISCHARGING,
    FAKE_ABC_TERMINAL_CONTROLLER_STATE_CHARGING
} fake_abc_terminalController_ChargingState_t;

void
fake_abc_terminalController_setUpowerState(fake_abc_terminalController_ChargingState_t chargingState);

bool
fake_abc_terminalController_calledUpower(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
