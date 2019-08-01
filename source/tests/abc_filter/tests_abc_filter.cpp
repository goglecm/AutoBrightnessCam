#include <gtest/gtest.h>

#include "abc_logging_service/abc_logging_service.h"

#include "abc_filter/abc_filter.h"

#include <cstring>

#define DEFAULT_FILTER_SIZE 64U

static uint16_t s_vec[DEFAULT_FILTER_SIZE];

static abc_filter_AveragerData_t filter =
    {
        .SIZE = DEFAULT_FILTER_SIZE,
        .pValues = s_vec,
        .internal_pos = 0,
    };

class abc_filter: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // Clear the filter.
        memset(filter.pValues, 0, DEFAULT_FILTER_SIZE * sizeof(s_vec[0]));
        filter.internal_pos = 0;

        ASSERT_TRUE(abc_loggingService_setLogName((std::string(::testing::UnitTest::GetInstance()->current_test_info()->test_case_name()) + "_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() + ".log").c_str()));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());

        // code here will execute just before the test ensues
    }
};

TEST_F(abc_filter, averages_64_values)
{
    uint16_t output = 0;
    for (uint16_t i = 0; i < DEFAULT_FILTER_SIZE; ++i)
    {
        ASSERT_TRUE(abc_filter_average(&filter, i, &output));
    }

    uint32_t avg = 0;
    for (uint16_t i = 0; i < DEFAULT_FILTER_SIZE; ++i)
    {
        avg += i;
    }

    avg /= DEFAULT_FILTER_SIZE;

    ASSERT_EQ(avg, output);
}

TEST_F(abc_filter, internal_position_wraps_around_the_filter_size)
{
    uint16_t output = 0;
    for (uint16_t i = 0; i < DEFAULT_FILTER_SIZE * 2; ++i)
    {
        ASSERT_TRUE(abc_filter_average(&filter, i, &output));

        ASSERT_EQ((i + 1) % DEFAULT_FILTER_SIZE, filter.internal_pos);
    }
}

TEST_F(abc_filter, filter_fails_on_bad_arguments)
{
    ASSERT_FALSE(abc_filter_average(NULL, 0, NULL));
}

TEST_F(abc_filter, filter_fails_when_the_internal_position_is_beyond_the_filter_size)
{
    filter.internal_pos = DEFAULT_FILTER_SIZE;

    uint16_t output = 0;
    ASSERT_FALSE(abc_filter_average(&filter, 0, &output));
}

TEST_F(abc_filter, filter_fails_when_the_filter_size_is_0)
{
    const uint16_t filterSize = 0;

    abc_filter_AveragerData_t f =
        {
            .SIZE = filterSize,
            .pValues = s_vec,
            .internal_pos = 0,
        };

    uint16_t output = 0;
    ASSERT_FALSE(abc_filter_average(&f, 0, &output));
}
