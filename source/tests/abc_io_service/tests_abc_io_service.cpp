#include <gtest/gtest.h>

#include "abc_io_service/abc_io_service.h"

#include "abc_logging_service/abc_logging_service.h"

#include <sstream>
#include <string>
#include <fstream>

class abc_io_service: public ::testing::Test
{
public:
    void SetUp(void)
    {
        // code here will execute just before the test ensues

        ASSERT_TRUE(abc_loggingService_setLogName((std::string(::testing::UnitTest::GetInstance()->current_test_info()->test_case_name()) + "_" + ::testing::UnitTest::GetInstance()->current_test_info()->name() + ".log").c_str()));

        ABC_LOG("\n ## Starting test %s ## \n", ::testing::UnitTest::GetInstance()->current_test_info()->name());
    }
};

template <typename T> static std::string
to_str(const T a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
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
    setValue<const char *>(fileName, "");
}

TEST_F(abc_io_service, write_to_non_existant_file_creates_the_file_and_writes_to_it)
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

TEST_F(abc_io_service, file_is_written_an_integer)
{
    const std::string filename(std::string(__func__) + ".test");

    const int intWritten = 50;

    ASSERT_TRUE(abc_ioService_write(intWritten, filename.c_str()));

    std::ifstream infile(filename.c_str());

    std::string line;
    std::getline(infile, line);

    ASSERT_EQ(line, to_str(intWritten));
}

TEST_F(abc_io_service, write_to_invalid_file_fails)
{
    ASSERT_FALSE(abc_ioService_write(0, NULL));
}

TEST_F(abc_io_service, read_fails_when_the_return_pointer_is_invalid)
{
    const std::string filename(std::string(__func__) + ".test");

    setValue(filename, "10");

    ASSERT_FALSE(abc_ioService_read(NULL, filename.c_str()));
}

TEST_F(abc_io_service, read_fails_when_file_does_not_exist_or_has_a_bad_name)
{
    const std::string filename(std::string(__func__) + ".test");

    ASSERT_EQ(0, std::remove(filename.c_str()));

    int ret;

    ASSERT_FALSE(abc_ioService_read(&ret, filename.c_str()));
}

TEST_F(abc_io_service, read_fails_when_file_is_empty)
{
    const std::string filename(std::string(__func__) + ".test");

    createFile(filename);

    int ret;

    ASSERT_FALSE(abc_ioService_read(&ret, filename.c_str()));
}

TEST_F(abc_io_service, read_fails_when_file_has_alphanumeric_data)
{
    const std::string filename(std::string(__func__) + ".test");

    setValue(filename, "abc10");

    int ret;

    ASSERT_FALSE(abc_ioService_read(&ret, filename.c_str()));
}
