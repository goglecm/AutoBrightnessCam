#ifndef AUTOBRIGHTNESSCAM_ABC_POWER_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_ABC_POWER_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum abc_powerController_State_t
{
    ABC_POWER_CONTROLLER_STATE_UNKNOWN,
    ABC_POWER_CONTROLLER_STATE_DISCHARGING,
    ABC_POWER_CONTROLLER_STATE_CHARGING,
    ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED,
    ABC_POWER_CONTROLLER_STATE__COUNT

} abc_powerController_State_t;

bool
abc_powerController_isCharging(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_POWER_CONTROLLER_H
