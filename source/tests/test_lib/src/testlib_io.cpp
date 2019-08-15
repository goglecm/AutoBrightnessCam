#include "testlib_io.h"

#include <sys/stat.h>

bool
testlib_io_exists(const std::string &name)
{
    static struct stat buffer;
    return 0 == stat(name.c_str(), &buffer);
}
