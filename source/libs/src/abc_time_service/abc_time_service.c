#include "abc_time_service/abc_time_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include <stddef.h>
#include <unistd.h>

time_t
abc_timeService_get(void)
{
    return time(NULL);
}

void
abc_timeService_sleep_ms(const unsigned ms)
{
    usleep(ms * 1000U);
}
