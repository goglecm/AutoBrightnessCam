#include <gtest/gtest.h>

#include "abc_terminal_controller/abc_terminal_controller.h"

#include <sstream>
#include <string>
#include <fstream>

template <typename T> static std::string
to_str(const T a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

TEST(abc_terminal_controller_files, write_to_non_existant_file_creates_the_file_and_writes_to_it)
{
    const std::string filename(std::string(__func__) + ".test");

    std::remove(filename.c_str());

    const int intWritten = 10;

    ASSERT_TRUE(abc_terminalController_writeFile(intWritten, filename.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, to_str(intWritten));
}

TEST(abc_terminal_controller_files, file_is_written_an_integer)
{
    const std::string filename(std::string(__func__) + ".test");

    const int intWritten = 50;

    ASSERT_TRUE(abc_terminalController_writeFile(intWritten, filename.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, to_str(intWritten));
}

TEST(abc_terminal_controller_files, write_to_bad_file_causes_error)
{
    ASSERT_FALSE(abc_terminalController_writeFile(0, NULL));
}

TEST(abc_terminal_controller_commands, command_without_return_is_executed)
{
    const std::string filename(std::string(__func__) + ".test");

    const std::string cmd = "echo Hello > " + filename;

    ASSERT_TRUE(abc_terminalController_send(cmd.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, "Hello");
}

TEST(abc_terminal_controller_commands, bad_command_without_return_reports_false)
{
    ASSERT_FALSE(abc_terminalController_send(NULL));
}

TEST(abc_terminal_controller_commands, command_returning_double_is_executed)
{
    const double expectedResult = 522.9;

    const std::string cmd("echo " + to_str(expectedResult));

    double result = 0;

    ASSERT_TRUE(abc_terminalController_sendReturnDbl(&result, cmd.c_str()));

    ASSERT_DOUBLE_EQ(expectedResult, result);
}

TEST(abc_terminal_controller_commands, command_returning_string_is_executed)
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
