#include <gtest/gtest.h>

#include "abc_ambient_brightness_controller/abc_ambient_brightness_controller.h"
#include "abc_logging_service/abc_logging_service.h"
#include "abc_ambient_brightness_controller/fake_abc_terminal_controller.h"

class abc_ambient_brightness_controller: public ::testing::Test
{
public:
    void SetUp(void)
    {
        ASSERT_TRUE(abc_loggingService_setLogName((std::string(::testing::UnitTest::GetInstance()->current_test_info()->test_case_name()) + "_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() + ".log").c_str()));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());

        fake_abc_terminalController_resetNumCalcs();

        fake_abc_terminalController_resetNumShots();
    }
};

TEST_F(abc_ambient_brightness_controller, one_picture_is_shot_externally_when_ambient_brightness_is_read)
{
    double readValue;

    ASSERT_TRUE(abc_ambientBrightnessController_get(&readValue));

    ASSERT_EQ(1, fake_abc_terminalController_getNumShots());
}

TEST_F(abc_ambient_brightness_controller, picture_brightness_is_calculated_externally_when_ambient_brightness_is_read)
{
    double readValue;

    ASSERT_TRUE(abc_ambientBrightnessController_get(&readValue));

    ASSERT_EQ(1, fake_abc_terminalController_getNumCalcs());
}
