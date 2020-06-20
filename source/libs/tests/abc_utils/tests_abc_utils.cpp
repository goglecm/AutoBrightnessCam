#include <gtest/gtest.h>

#include "abc_utils/abc_utils.h"

#include "abc_logging_service/abc_logging_service.h"

#include "testlib_io.h"

class abc_utils: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName(SPECIFIC_LOG_NAME));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());
    }
};

TEST_F(abc_utils, int_string_with_preceeding_spaces_is_converted_to_int)
{
    int result = -1;
    std::string strToConvert("  123");

    ASSERT_TRUE(abc_utils_strToInt(&result, strToConvert.c_str()));

    ASSERT_EQ(123, result);
}

TEST_F(abc_utils, negative_int_string_is_converted_to_int)
{
    int result = -1;
    std::string strToConvert("-123");

    ASSERT_TRUE(abc_utils_strToInt(&result, strToConvert.c_str()));

    ASSERT_EQ(-123, result);
}

TEST_F(abc_utils, positive_int_string_is_converted_to_int)
{
    int result = -1;
    std::string strToConvert("123");

    ASSERT_TRUE(abc_utils_strToInt(&result, strToConvert.c_str()));

    ASSERT_EQ(123, result);
}

TEST_F(abc_utils, alphanumeric_string_cannot_be_converted_to_int)
{
    int result = -1;
    std::string strToConvert("abc123");

    ASSERT_FALSE(abc_utils_strToInt(&result, strToConvert.c_str()));

    // Also check to make sure the resultant integer hasn't changed.
    ASSERT_EQ(-1, result);
}

