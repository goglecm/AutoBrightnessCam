#include <gtest/gtest.h>

#include "abc_backlight_brightness_controller/abc_backlight_brightness_controller.h"

#include "abc_io_service/abc_io_service.h"

#include "abc_backlight_brightness_controller/fake_abc_terminal_controller.h"

#include "abc_logging_service/abc_logging_service.h"

#include <fstream>

static const uint16_t
s_DEFAULT_MAX = 6900;

static const char s_CURRENT_BRIGHTNESS_PATH[] = "current_brightness";

static const char s_MAX_BRIGHTNESS_PATH[] = "max_brightness";

static double
getMidBrightness(void)
{
    return (g_abc_BacklightBrightnessController_MAX -
            g_abc_BacklightBrightnessController_MIN) / 2 +
           g_abc_BacklightBrightnessController_MIN;
}

static uint16_t
toRawBrightness(const double target)
{
    return target / 100.0 * s_DEFAULT_MAX;
}

inline bool exists(const std::string &name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

template <typename T> static void
setValue(const std::string &fileName, const T value)
{
    if (exists(fileName))
    {
        ASSERT_EQ(0, std::remove(fileName.c_str()));
    }

    std::stringstream outValue;

    outValue << value;

    std::ofstream outfile (fileName.c_str());

    ABC_LOG("written %s to file %s", outValue.str().c_str(), fileName.c_str());

    outfile << outValue.str() << std::endl;

    outfile.close();
}

static void
createFile(const std::string &fileName)
{
    if (exists(fileName))
    {
        ASSERT_EQ(0, std::remove(fileName.c_str()));
    }

    std::ofstream outfile (fileName.c_str());

    outfile.close();
}

class abc_backlight_brightness_controller: public ::testing::Test
{

public:
    abc_backlight_brightness_controller(void)
    {
        // initialization code here
    }

    void SetUp(void)
    {
        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());

        // code here will execute just before the test ensues

        abc_backlightBrightnessController_setCurrentPath(s_CURRENT_BRIGHTNESS_PATH);
        abc_backlightBrightnessController_setMaxPath(s_MAX_BRIGHTNESS_PATH);

        abc_backlightBrightnessController_resetMax();

        setValue<int>(std::string(s_MAX_BRIGHTNESS_PATH), s_DEFAULT_MAX);

        setValue<int>(std::string(s_CURRENT_BRIGHTNESS_PATH), toRawBrightness(getMidBrightness()));

        fake_abc_terminalController_resetNumWriteCalls();
    }

    void TearDown(void)
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~abc_backlight_brightness_controller(void)
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
};

TEST_F(abc_backlight_brightness_controller, backlight_brightness_is_set_to_new_value)
{
    // Mid point between min and max
    const double target = getMidBrightness();

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(target),
              fake_abc_terminalController_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, backlight_brightness_does_not_exceed_maximum_brightness)
{
    const double target = g_abc_BacklightBrightnessController_MAX * 1.5;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(g_abc_BacklightBrightnessController_MAX),
              fake_abc_terminalController_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, backlight_brightness_does_not_recede_minimum_brightness)
{
    const double target = g_abc_BacklightBrightnessController_MIN / 2;

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(toRawBrightness(g_abc_BacklightBrightnessController_MIN),
              fake_abc_terminalController_getCurrentBrightness());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_the_maximum_brightness_file_does_not_exist_or_has_a_bad_name)
{
    const double target = (g_abc_BacklightBrightnessController_MIN + g_abc_BacklightBrightnessController_MAX) / 2;

    // Remove file (this can also be done by specifying a bad file name)
    ASSERT_EQ(0, std::remove(s_MAX_BRIGHTNESS_PATH));

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_terminalController_getNumWrites());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_the_maximum_brightness_file_is_empty)
{
    const double target = (g_abc_BacklightBrightnessController_MIN + g_abc_BacklightBrightnessController_MAX) / 2;

    createFile(s_MAX_BRIGHTNESS_PATH);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_terminalController_getNumWrites());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_the_maximum_brightness_file_has_bad_data)
{
    const double target = (g_abc_BacklightBrightnessController_MIN + g_abc_BacklightBrightnessController_MAX) / 2;

    setValue<const char *const>(s_MAX_BRIGHTNESS_PATH, "hello");

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_terminalController_getNumWrites());
}

TEST_F(abc_backlight_brightness_controller, brightness_is_not_set_when_the_maximum_brightness_is_zero)
{
    // Mid point between min and max
    const double target = getMidBrightness();

    setValue<int>(s_MAX_BRIGHTNESS_PATH, 0);

    abc_backlightBrightnessController_set(target);

    ASSERT_EQ(0, fake_abc_terminalController_getNumWrites());
}
