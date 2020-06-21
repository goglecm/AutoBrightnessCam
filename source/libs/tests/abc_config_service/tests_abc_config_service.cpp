#include <gtest/gtest.h>

#include "abc_config_service/abc_config_service.h"

#include "abc_config_service/fake_abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include "testlib_io.h"
#include "testlib_parsing.h"

class abc_config_service: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName(SPECIFIC_LOG_NAME));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());
    }
};

TEST_F(abc_config_service, read_int_value_from_existing_key_pair)
{
    const int expectedValue = 5;
    const std::string configEntry(
            "sampling_period = " +
            testlib_parsing_toStr(expectedValue));

    fake_abc_ioService_setConfigEntry(configEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service, read_int_value_from_existing_key_pair_with_comment)
{
    const int expectedValue = 5;
    const std::string configEntry(
            "sampling_period = " +
            testlib_parsing_toStr(expectedValue) +
            " # Comment");

    fake_abc_ioService_setConfigEntry(configEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service, read_negative_int_value_from_existing_key_pair)
{
    const int expectedValue = -5;
    const std::string configEntry(
            "sampling_period = " +
            testlib_parsing_toStr(expectedValue));

    fake_abc_ioService_setConfigEntry(configEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service, fail_to_read_bad_value_from_existing_key_pair_but_pick_up_default)
{
    const std::string configEntry("sampling_period = abc");
    const std::string defaultConfigEntry("sampling_period = 123");

    fake_abc_ioService_setConfigEntry(configEntry.c_str());
    fake_abc_ioService_setDefaultConfigEntry(defaultConfigEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service, fail_to_read_bad_value_from_existing_key_pair_and_bad_default)
{
    const std::string configEntry("sampling_period = abc");
    const std::string defaultConfigEntry("sampling_period = xyz");

    fake_abc_ioService_setConfigEntry(configEntry.c_str());
    fake_abc_ioService_setDefaultConfigEntry(defaultConfigEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_FALSE(abc_configService_get(key, &actualValue));

    // Ensure the value hasn't changed.
    ASSERT_EQ(-1, actualValue);
}

TEST_F(abc_config_service, fail_to_read_key_with_prefix)
{
    const std::string configEntry(" sampling_period");
    const std::string defaultConfigEntry("sampling_period = 123");

    fake_abc_ioService_setConfigEntry(configEntry.c_str());
    fake_abc_ioService_setDefaultConfigEntry(defaultConfigEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service, fail_to_read_bad_key)
{
    const std::string configEntry("bad_sampling_period");
    const std::string defaultConfigEntry("sampling_period = 123");

    fake_abc_ioService_setConfigEntry(configEntry.c_str());
    fake_abc_ioService_setDefaultConfigEntry(defaultConfigEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service, fail_to_read_missing_value_from_existing_key_pair)
{
    const std::string configEntry("sampling_period = ");
    const std::string defaultConfigEntry("sampling_period = 123");

    fake_abc_ioService_setConfigEntry(configEntry.c_str());
    fake_abc_ioService_setDefaultConfigEntry(defaultConfigEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service, fail_to_read_missing_value_from_existing_key_pair_comment)
{
    const std::string configEntry("sampling_period = # Comment");
    const std::string defaultConfigEntry("sampling_period = 123");

    fake_abc_ioService_setConfigEntry(configEntry.c_str());
    fake_abc_ioService_setDefaultConfigEntry(defaultConfigEntry.c_str());

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}
