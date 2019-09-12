#ifndef AUTOBRIGHTNESSCAM_TESTLIB_IO_H
#define AUTOBRIGHTNESSCAM_TESTLIB_IO_H

#include <string>

#define SPECIFIC_LOG_NAME \
((std::string(::testing::UnitTest::GetInstance()->current_test_info()->test_case_name()) + \
"_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() + ".log").c_str())

// Test run path is in the current directory by default.
#ifndef ABC_TESTRUN_PATH
#define ABC_TESTRUN_PATH "."
#endif

#define DEFAULT_FILENAME \
(( std::string(ABC_TESTRUN_PATH) + "/" + \
std::string(  ::testing::UnitTest::GetInstance()->current_test_info()->test_case_name()) + \
"_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() + ".test"  ).c_str())

bool
testlib_io_exists(const std::string &name);

#endif //AUTOBRIGHTNESSCAM_TESTLIB_IO_H
