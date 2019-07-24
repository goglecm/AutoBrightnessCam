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

class abc_logging_service: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName((std::string(::testing::UnitTest::GetInstance()->current_test_info()->test_case_name()) + "_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() + ".log").c_str()));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());
    }
};

static void resetLogger(void)
{
    g_isFirstLog = true;
    ABC_LOG("First log");
}

static void skipResetState(std::ifstream &infile)
{
    std::string line;
    std::getline(infile, line); // Skip initial message
    std::getline(infile, line); // Skip initial new line
    std::getline(infile, line); // Skip the first log new line
    std::getline(infile, line); // Skip the first log (which is also a new line)
}

static void checkLogFormat(const std::string &targetMessage,
                           const std::string &logType,
                           const std::string &funcName)
{
    std::ifstream infile(g_logFilename);
    skipResetState(infile);

    // Log format:
    // \n[logType: ]funcName: message
    std::string fullLogMessage = (logType.empty() ? "" : logType + ": ") +
                                 funcName + ": " +
                                 targetMessage;
    std::string line;
    std::getline(infile, line);
    ASSERT_EQ(fullLogMessage, line);
}


TEST_F(abc_logging_service, initial_message_is_logged_before_first_log)
{
    resetLogger();

    std::ifstream infile(g_logFilename);

    std::string line;

    std::getline(infile, line);
    std::string initialLog("Starting logs");
    ASSERT_EQ(initialLog, line);

    std::getline(infile, line);
    std::string newLineAfterInitialMessage("");
    ASSERT_EQ(newLineAfterInitialMessage, line);
}

TEST_F(abc_logging_service, message_is_logged_in_a_file_with_newline_and_function_name_before_it)
{
    resetLogger();

    std::string targetMessage("Hello world!");

    ABC_LOG(targetMessage.c_str());

    checkLogFormat(targetMessage, "", __func__);
}

TEST_F(abc_logging_service, warning_is_logged_in_a_file_with_newline_and_warning_and_function_name_before_it)
{
    resetLogger();

    std::string targetMessage("something unexpected happened");

    ABC_LOG_WRN(targetMessage.c_str());

    checkLogFormat(targetMessage, "WARNING", __func__);
}

TEST_F(abc_logging_service, error_is_logged_in_a_file_with_newline_and_error_and_function_name_before_it)
{
    resetLogger();

    std::string targetMessage("something bad happened");

    ABC_LOG_ERR(targetMessage.c_str());

    checkLogFormat(targetMessage, "ERROR", __func__);
}
