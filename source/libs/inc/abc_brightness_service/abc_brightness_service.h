#ifndef AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned abc_brightnessService_PeriodSec_t; // Seconds

typedef enum abc_brightnessService_Status_t
{
    ABC_BRIGHTNESSSERVICE_STOPPED,
    ABC_BRIGHTNESSSERVICE_STARTED,

} abc_brightnessService_Status_t;

typedef enum abc_brightnessService_Result_t
{
    ABC_BRIGHTNESSSERVICE_FAILURE,
    ABC_BRIGHTNESSSERVICE_SUCCESS,

} abc_brightnessService_Result_t;

extern const abc_brightnessService_PeriodSec_t
g_abc_brightnessService_DEFAULT_PERIOD;

extern const abc_brightnessService_PeriodSec_t
g_abc_brightnessService_MIN_PERIOD;

extern const abc_brightnessService_PeriodSec_t
g_abc_brightnessService_MAX_PERIOD;


// Service control

void
abc_brightnessService_stop(void);

void
abc_brightnessService_start(void);

abc_brightnessService_Result_t
abc_brightnessService_wakeUp(void);


// Period control

abc_brightnessService_Result_t
abc_brightnessService_setPeriod(abc_brightnessService_PeriodSec_t period);

abc_brightnessService_PeriodSec_t
abc_brightnessService_getPeriod(void);



#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_BRIGHTNESS_SERVICE_H
