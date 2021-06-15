#include <gtest/gtest.h>

#include "abc_config_service/abc_config_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include "testlib_io.h"
#include "testlib_parsing.h"

#include <sstream>
#include <string>
#include <fstream>

class abc_config_service_libconfig: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName(SPECIFIC_LOG_NAME));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());
    }

    void TearDown(void)
    {
        if (testlib_io_exists(ABC_CONFIG_FILENAME))
        {
            ASSERT_EQ(0, std::remove(ABC_CONFIG_FILENAME));
        }

        if (testlib_io_exists(ABC_CONFIG_DEFAULTS_FILENAME))
        {
            ASSERT_EQ(0, std::remove(ABC_CONFIG_DEFAULTS_FILENAME));
        }
    }
};

template <typename T> static void
setValue(const std::string &fileName, const T value)
{
    if (testlib_io_exists(fileName))
    {
        ASSERT_EQ(0, std::remove(fileName.c_str()));
    }

    std::stringstream outValue;

    outValue << value;

    std::ofstream outfile (fileName.c_str());

    ABC_LOG("written `%s` to file `%s`", outValue.str().c_str(), fileName.c_str());

    outfile << outValue.str() << std::endl;

    outfile.close();
}

TEST_F(abc_config_service_libconfig, read_int_value_from_key_pair_with_many_spaces)
{
    const int expectedValue = 5;
    const std::string configEntry(
            "sampling_period  \t  =  \t   " +
            testlib_parsing_toStr(expectedValue) + "  \t  \n");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service_libconfig, read_int_value_from_key_pair_without_spaces)
{
    const int expectedValue = 5;
    const std::string configEntry(
            "sampling_period=" +
            testlib_parsing_toStr(expectedValue));

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service_libconfig, read_int_value_from_key_pair)
{
    const int expectedValue = 5;
    const std::string configEntry(
            "sampling_period = " +
            testlib_parsing_toStr(expectedValue));

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service_libconfig, read_int_value_from_key_pair_with_comment)
{
    const int expectedValue = 5;
    const std::string configEntry(
            "sampling_period = " +
            testlib_parsing_toStr(expectedValue) +
            " # Comment");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service_libconfig, read_negative_int_value_from_key_pair)
{
    const int expectedValue = -5;
    const std::string configEntry(
            "sampling_period = " +
            testlib_parsing_toStr(expectedValue));

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_bad_value_from_key_pair_but_pick_up_default)
{
    const std::string configEntry("sampling_period = abc");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_bad_value_from_key_pair_and_bad_default)
{
    const std::string configEntry("sampling_period = abc");
    const std::string defaultConfigEntry("sampling_period = xyz");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_FALSE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(-1, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_key_with_prefix)
{
    const std::string configEntry(" sampling_period");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_bad_key)
{
    const std::string configEntry("bad_sampling_period");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_missing_int_value_from_key_pair)
{
    const std::string configEntry("sampling_period = ");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_missing_int_value_from_key_pair_with_comment)
{
    const std::string configEntry("sampling_period = # Comment");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_int_value_in_comment_from_key_pair_before_equal)
{
    const std::string configEntry("sampling_period # = 123");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_int_value_in_comment_from_key_pair_after_equal)
{
    const std::string configEntry("sampling_period = # 5");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_int_value_from_similar_but_different_key)
{
    const std::string configEntry("sampling_period_bad = 5");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_int_value_when_entry_is_missing)
{
    setValue<std::string>(ABC_CONFIG_FILENAME, "");
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, "");

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_FALSE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(-1, actualValue);
}

TEST_F(abc_config_service_libconfig, fail_to_read_key_if_defined_multiple_times)
{
    const std::string configEntry(
            "sampling_period = 42\n"
            "sampling_period = 56");
    const std::string defaultConfigEntry("sampling_period = 123");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, defaultConfigEntry);

    int actualValue = -1;
    const abc_configService_Key_t key = ABC_CONFIG_SERVICE_KEY_SAMPLING_PERIOD;
    ASSERT_TRUE(abc_configService_get(key, &actualValue));

    ASSERT_EQ(123, actualValue);
}

TEST_F(abc_config_service_libconfig, read_string_from_list_within_bounds)
{
    const std::string configEntry("battery_files = [\"one\", \"two\", \"three\"]");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, configEntry);

    char element[10] = { '\0' };
    int index = 1;

    const bool result = abc_configService_getStrElem(
            ABC_CONFIG_SERVICE_KEY_BATTERY_FILES,
            element,
            sizeof(element) / sizeof(element[0]),
            index);

    ASSERT_TRUE(result);

    ASSERT_STREQ(element, "two");
}

TEST_F(abc_config_service_libconfig, read_string_from_list_out_of_bounds)
{
    const std::string configEntry("battery_files = [\"one\", \"two\", \"three\"]");

    setValue<std::string>(ABC_CONFIG_FILENAME, configEntry);
    setValue<std::string>(ABC_CONFIG_DEFAULTS_FILENAME, configEntry);

    char element[10] = { '\0' };
    int index = 3;

    const bool result = abc_configService_getStrElem(
            ABC_CONFIG_SERVICE_KEY_BATTERY_FILES,
            element,
            sizeof(element) / sizeof(element[0]),
            index);

    ASSERT_FALSE(result);

    ASSERT_STREQ(element, "");
}
