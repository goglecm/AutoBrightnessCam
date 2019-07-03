#include <gtest/gtest.h>

#include "abc_terminal_controller/abc_terminal_controller.h"

#include <sstream>
#include <string>
#include <fstream>

static std::string
to_str(const int a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

TEST(abc_terminal_controller_files, file_is_written_an_integer)
{
    const std::string filename(std::string(__func__) + ".test");

    const int intWritten = 50;

    abc_terminalController_writeFile(intWritten, filename.c_str());

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, to_str(intWritten));
}
