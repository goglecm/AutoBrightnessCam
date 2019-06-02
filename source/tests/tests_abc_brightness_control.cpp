#include "abc_brightness_control.h"

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>

#include <stdint.h>

static void
createDisplay(const std::string &displayPath,
              const std::string &displayMaxBrightnessPath,
              const uint16_t initialBrightnessValue)
{
    std::ofstream outfile(displayPath.c_str());

    outfile << std::dec << initialBrightnessValue << std::endl;

    outfile.close();

    std::ofstream outfileMax(displayMaxBrightnessPath.c_str());

    outfileMax << std::dec << initialBrightnessValue * 2 + 123 << std::endl;

    outfileMax.close();
}

TEST(ABC_brightness_control, setAndGetTheBrightnessOfADisplay)
{
    const std::string displayPath("testDisplay.out");
    const std::string displayMaxBrightnessPath("testMaxDisplay.out");

    createDisplay(displayPath, displayMaxBrightnessPath, 10);

    const abc_DisplayBrightnessInfo_t testDisplayInfo =
    {
        .pDisplayBrightnessPath = displayPath.c_str(),
        .pMaxDisplayBrightnessPath = displayMaxBrightnessPath.c_str(),
    };

    abc_setBrightness(&testDisplayInfo, 50.0);

    double readBrightness = -1;

    abc_getBrightness(&testDisplayInfo, &readBrightness);

    ASSERT_GE(readBrightness, 45);

    ASSERT_LE(readBrightness, 55);
}
