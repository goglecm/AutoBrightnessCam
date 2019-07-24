#ifndef AUTOBRIGHTNESSCAM_ABC_TIME_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_TIME_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdint.h>

// Warning! Direct wrapper. Not tested.

time_t
abc_timeService_get(void);

void
abc_timeService_sleep_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_TIME_SERVICE_H
