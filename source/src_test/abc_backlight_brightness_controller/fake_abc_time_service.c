#include "abc_time_service/abc_time_service.h"

#include <assert.h>

void
abc_timeService_sleep_ms(const uint32_t ms)
{
    assert(ms > 0);
    (void) ms;
}
