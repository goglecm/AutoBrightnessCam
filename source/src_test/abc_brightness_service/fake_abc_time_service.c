#include "abc_time_service/abc_time_service.h"
#include "abc_brightness_service/fake_abc_time_service.h"

static time_t s_time;

void
fake_abc_timeService_forward(const unsigned seconds)
{
    s_time += seconds;
}

time_t
abc_timeService_get(void)
{
    return s_time;
}
