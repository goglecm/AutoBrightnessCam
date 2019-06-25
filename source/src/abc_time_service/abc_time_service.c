#include "abc_time_service.h"

#include <assert.h>
#include <stddef.h>

time_t
abc_timeService_get(void)
{
    return time(NULL);
}
