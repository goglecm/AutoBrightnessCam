#ifndef AUTOBRIGHTNESSCAM_ABC_POWER_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_ABC_POWER_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif



#ifndef ABC_HAS_UPOWER

#   error "ABC_HAS_UPOWER is not defined"

#endif // ABC_HAS_UPOWER

#if ABC_HAS_UPOWER != 0 && ABC_HAS_UPOWER != 1

#   error "Bad value for ABC_HAS_UPOWER"

#endif // ABC_HAS_UPOWER



#include <stdbool.h>



typedef enum abc_powerController_State_t
{
    ABC_POWER_CONTROLLER_STATE_UNKNOWN,
    ABC_POWER_CONTROLLER_STATE_DISCHARGING,
    ABC_POWER_CONTROLLER_STATE_CHARGING,
    ABC_POWER_CONTROLLER_STATE_FULLY_CHARGED,
    ABC_POWER_CONTROLLER_STATE__COUNT

} abc_powerController_State_t;



#if ABC_HAS_UPOWER == 0

bool
abc_powerController_setBatteryStatePath(const char *batteryStatePath);

void
abc_powerController_resetBatteryStatePath(void);

#endif // ABC_HAS_UPOWER



bool
abc_powerController_isCharging(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_POWER_CONTROLLER_H
