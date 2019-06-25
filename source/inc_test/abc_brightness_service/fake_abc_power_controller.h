#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_POWER_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_POWER_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    fake_abc_PowerState_DISCHARGING,
    fake_abc_PowerState_CHARGING
} fake_abc_PowerState_t;

void fake_abc_powerController_setState(fake_abc_PowerState_t source);

#ifdef __cplusplus
}
#endif


#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_POWER_CONTROLLER_H
