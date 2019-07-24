#include <gtest/gtest.h>

#include "abc_time_service/abc_time_service.h"

#include "abc_brightness_service/fake_abc_time_service.h"

#include "abc_logging_service/abc_logging_service.h"

class fake_abc_time_service: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName((std::string(::testing::UnitTest::GetInstance()->current_test_info()->test_case_name()) + "_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() + ".log").c_str()));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());
    }
};

TEST_F(fake_abc_time_service, current_time_is_incremented_by_12_seconds)
{
    const time_t expectedTime = abc_timeService_get() + 12;

    fake_abc_timeService_forward(12);

    ASSERT_EQ(expectedTime, abc_timeService_get());
}
