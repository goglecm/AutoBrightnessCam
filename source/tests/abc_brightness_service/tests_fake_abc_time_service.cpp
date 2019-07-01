#include <gtest/gtest.h>

#include "abc_time_service/abc_time_service.h"

#include "abc_brightness_service/fake_abc_time_service.h"

TEST(fake_abc_time_service, current_time_is_incremented_by_12_seconds)
{
    const time_t expectedTime = abc_timeService_get() + 12;

    fake_abc_timeService_forward(12);

    ASSERT_EQ(expectedTime, abc_timeService_get());
}
