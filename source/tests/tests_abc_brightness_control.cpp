#include "abc_brightness_control.h"

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>

#include <stdint.h>

class test_DisplayBrightness_t
{
    const std::string displayPath_;

    const std::string displayMaxBrightnessPath_;

public:
    static const uint16_t s_MAX_BRIGHTNESS = 100;

    explicit test_DisplayBrightness_t(const std::string &displayPath,
                                      const std::string &displayMaxBrightnessPath,
                                      const double initialBrightnessValue):
        displayPath_(displayPath),
        displayMaxBrightnessPath_(displayMaxBrightnessPath)
    {
        std::ofstream outfile(displayPath.c_str());

        outfile << std::dec << (initialBrightnessValue / 100.0) * s_MAX_BRIGHTNESS << std::endl;

        outfile.close();

        std::ofstream outfileMax(displayMaxBrightnessPath.c_str());

        outfileMax << std::dec << s_MAX_BRIGHTNESS << std::endl;

        outfileMax.close();
    }

    double getBrightness(void)
    {
        std::ifstream displayFile(displayPath_.c_str());

        uint16_t currentBrightness = 0;

        displayFile >> currentBrightness;

        displayFile.close();

        return (currentBrightness / 100.0) * 100.0;
    }
};

TEST(ABC_brightness_control, setAndGetTheBrightnessOfADisplay)
{
    // Create a display.
    const std::string displayPath("testDisplay.out");
    const std::string displayMaxBrightnessPath("testMaxDisplay.out");
    test_DisplayBrightness_t testDisplay(displayPath, displayMaxBrightnessPath, 10.0);

    // Set the display brightness.
    const abc_DisplayBrightnessInfo_t testDisplayInfo =
    {
        .pDisplayBrightnessPath = displayPath.c_str(),
        .pMaxDisplayBrightnessPath = displayMaxBrightnessPath.c_str(),
    };

    abc_setBrightness(&testDisplayInfo, 50.0);

    // Check the display brightness.
    const double readBrightness = testDisplay.getBrightness();

    ASSERT_GE(readBrightness, 49);

    ASSERT_LE(readBrightness, 51);
}
