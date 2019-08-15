#include <gtest/gtest.h>

#include "abc_terminal_controller/abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

#include "testlib_io.h"
#include "testlib_parsing.h"

#include <string>
#include <fstream>

class abc_terminal_controller_commands: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName(SPECIFIC_LOG_NAME));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());
    }
};

TEST_F(abc_terminal_controller_commands, command_without_return_is_executed)
{
    const std::string filename(DEFAULT_FILENAME);

    if (testlib_io_exists(filename))
    {
        ASSERT_EQ(0, std::remove(filename.c_str()));
    }

    const std::string cmd = "echo Hello > " + filename;

    ASSERT_TRUE(abc_terminalController_send(cmd.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, "Hello");
}

TEST_F(abc_terminal_controller_commands, bad_command_without_return_reports_false)
{
    ASSERT_FALSE(abc_terminalController_send(NULL));
}

TEST_F(abc_terminal_controller_commands, command_returning_double_is_executed)
{
    const double expectedResult = 522.9;

    const std::string cmd("echo " + testlib_parsing_toStr(expectedResult));

    double result = 0;

    ASSERT_TRUE(abc_terminalController_sendReturnDbl(&result, cmd.c_str()));

    ASSERT_DOUBLE_EQ(expectedResult, result);
}

TEST_F(abc_terminal_controller_commands, command_returning_string_is_executed)
{
    const std::string expectedResult("Hello");

    const std::string cmd("echo " + expectedResult);

    const unsigned resultLen = 8;

    char result[resultLen];

    memset(result, 0, resultLen);

    ASSERT_TRUE(abc_terminalController_sendReturnStr(8, result, cmd.c_str()));

    // Limit the string length to prevent overflows.
    result[resultLen - 1] = '\0';

    // Kill the last newline character.
    result[strlen(result) - 1] = '\0';

    ASSERT_EQ(expectedResult, std::string(result));
}
