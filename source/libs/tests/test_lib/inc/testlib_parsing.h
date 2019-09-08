#ifndef AUTOBRIGHTNESSCAM_TESTLIB_PARSING_H
#define AUTOBRIGHTNESSCAM_TESTLIB_PARSING_H

#include <string>
#include <sstream>

template <typename T> static inline std::string
testlib_parsing_toStr(const T a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

#endif //AUTOBRIGHTNESSCAM_TESTLIB_PARSING_H
