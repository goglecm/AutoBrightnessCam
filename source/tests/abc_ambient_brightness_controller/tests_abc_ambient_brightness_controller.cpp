#include <gtest/gtest.h>

#include "abc_ambient_brightness_controller/abc_ambient_brightness_controller.h"
#include "abc_logging_service/abc_logging_service.h"
#include <abc_ambient_brightness_controller/fake_abc_terminal_controller.h>

TEST(abc_ambient_brightness_controller, one_picture_is_shot_externally_when_ambient_brightness_is_read)
{
    fake_abc_terminalController_resetNumShots();

    double readValue;

    ASSERT_TRUE(abc_ambientBrightnessController_get(&readValue));

    ASSERT_EQ(1, fake_abc_terminalController_getNumShots());
}

TEST(abc_ambient_brightness_controller, picture_brightness_is_calculated_externally_when_ambient_brightness_is_read)
{
    fake_abc_terminalController_resetNumCalcs();

    double readValue;

    ASSERT_TRUE(abc_ambientBrightnessController_get(&readValue));

    ASSERT_EQ(1, fake_abc_terminalController_getNumCalcs());
}
