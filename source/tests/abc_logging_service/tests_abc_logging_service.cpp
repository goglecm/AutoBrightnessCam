#include <gtest/gtest.h>

#include "abc_logging_service/abc_logging_service.h"

#include <sstream>
#include <string>
#include <fstream>

#ifdef ABC_LOGGING_ON

    #undef ABC_LOGGING_ON
    #define ABC_LOGGING_ON 1

#else

    #define ABC_LOGGING_ON 1

#endif // #ifdef ABC_LOGGING_ON

TEST(abc_logging_service, initial_message_is_logged_before_first_log)
{
    g_isFirstLog = true; // reset logger

    ABC_LOG("\n");

    std::ifstream infile(g_logFilename);

    std::string line;

    std::getline(infile, line);

    std::string initialLog("Starting logs");

    ASSERT_EQ(initialLog, line);

    std::getline(infile, line);

    std::string newLineAfterInitialMessage("");

    ASSERT_EQ(newLineAfterInitialMessage, line);
}

TEST(abc_logging_service, message_is_logged_in_a_file_with_newline_and_function_name_before_it)
{
    std::string targetLog("Hello world!");

    g_isFirstLog = true; // reset logger

    ABC_LOG(targetLog.c_str());

    std::ifstream infile(g_logFilename);

    std::string line;

    std::getline(infile, line); // Skip initial message
    std::getline(infile, line); // Skip initial new line

    std::string messageNewline("");

    std::getline(infile, line); // message newline

    ASSERT_EQ(messageNewline, line);

    std::string currentFunctionName(__func__);
    std::string message = currentFunctionName + ": " + targetLog;

    std::getline(infile, line); // message itself

    ASSERT_EQ(message, line);
}
