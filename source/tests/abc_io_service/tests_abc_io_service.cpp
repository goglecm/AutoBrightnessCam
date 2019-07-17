#include <gtest/gtest.h>

#include "abc_io_service/abc_io_service.h"

#include <sstream>
#include <string>
#include <fstream>

template <typename T> static std::string
to_str(const T a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

TEST(abc_io_service, write_to_non_existant_file_creates_the_file_and_writes_to_it)
{
    const std::string filename(std::string(__func__) + ".test");

    std::remove(filename.c_str());

    const int intWritten = 10;

    ASSERT_TRUE(abc_ioService_write(intWritten, filename.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, to_str(intWritten));
}

TEST(abc_io_service, file_is_written_an_integer)
{
    const std::string filename(std::string(__func__) + ".test");

    const int intWritten = 50;

    ASSERT_TRUE(abc_ioService_write(intWritten, filename.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, to_str(intWritten));
}

TEST(abc_io_service, write_to_invalid_file_fails)
{
    ASSERT_FALSE(abc_ioService_write(0, NULL));
}
