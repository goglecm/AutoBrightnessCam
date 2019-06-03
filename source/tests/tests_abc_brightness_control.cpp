#include "abc_brightness_control.h"

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>

#include <stdint.h>

class test_BrightnessDevice_t
{
    const std::string currentPath_;

    const std::string maxPath_;

public:
    static const uint16_t s_MAX_BRIGHTNESS_ = 150;

    explicit test_BrightnessDevice_t(const std::string &currentPath,
                                      const std::string &maxPath,
                                      const double initialBrightnessValue):
        currentPath_(currentPath),
        maxPath_(maxPath)
    {
        std::ofstream outfile(currentPath.c_str());

        outfile << std::dec
                << (initialBrightnessValue / 100.0) * s_MAX_BRIGHTNESS_
                << std::endl;

        outfile.close();

        std::ofstream outfileMax(maxPath.c_str());

        outfileMax << std::dec << s_MAX_BRIGHTNESS_ << std::endl;

        outfileMax.close();
    }

    double getCurrentBrightness(void) const
    {
        std::ifstream displayFile(currentPath_.c_str());

        uint16_t currentBrightness = 0;

        displayFile >> currentBrightness;

        displayFile.close();

        return ((double)currentBrightness / (double)s_MAX_BRIGHTNESS_) * 100.0;
    }
};

TEST(ABC_brightness_control, theBrightnessIsSetTo50Percent)
{
    const abc_Percentage_t initalBrightness = 10;
    const abc_Percentage_t targetBrightness = 50;

    // Create a display.
    const std::string currentPath("testBrightnessDeviceCurrent.out");
    const std::string maxPath("testBrightnessDeviceMax.out");

    const test_BrightnessDevice_t testDevice(currentPath,
                                             maxPath,
                                             initalBrightness);

    // Set the display brightness.
    const abc_BrightnessDeviceInfo_t brightnessInfo =
    {
        .pCurrent = currentPath.c_str(),
        .pMax = maxPath.c_str(),
    };

    abc_setBrightness(&brightnessInfo, targetBrightness);

    // Check the display brightness.
    const abc_Percentage_t readBrightness = testDevice.getCurrentBrightness();

    ASSERT_GE(readBrightness, targetBrightness - 1);
    ASSERT_LE(readBrightness, targetBrightness + 1);
}
