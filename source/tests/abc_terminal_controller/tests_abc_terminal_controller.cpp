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

    ASSERT_TRUE(abc_terminalController_writeFile(intWritten, filename.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, to_str(intWritten));
}

TEST(abc_terminal_controller_files, integer_is_read_from_file)
{
    const std::string filename(std::string(__func__) + ".test");

    int intRead = 60;

    std::ofstream outfile;
    outfile.open(filename.c_str());
    outfile << intRead;
    outfile.close();

    int actualInt = -1;
    ASSERT_TRUE(abc_terminalController_readFile(&actualInt, filename.c_str()));

    ASSERT_EQ(intRead, actualInt);
}
