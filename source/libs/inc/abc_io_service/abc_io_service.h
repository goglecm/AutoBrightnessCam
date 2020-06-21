#ifndef AUTOBRIGHTNESSCAM_ABC_IO_SERVICE_H
#define AUTOBRIGHTNESSCAM_ABC_IO_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool
abc_ioService_write(int value, const char *pFileName);

bool
abc_ioService_read(int *pValue, const char *pFileName);

bool
abc_ioService_readStr(char *pBuf, int bufMaxLen, const char *pFileName);

// - Finds and reads the full line starting with pStartStr into pRetStr.
// - pRetStr may include a new line char at the end and will be null terminated.
// - retStrMaxLen should include room for the null terminator. A value of 3
//   means the string can have up to 2 chars, followed by a null terminator.
bool
abc_ioService_readLineStartingWith(
        const char *pStartStr,
        char *pRetStr,
        int retStrBufMaxLen,
        const char *pFileName);

bool
abc_ioService_exists(const char *pFileName);

#ifdef __cplusplus
}
#endif

#endif // AUTOBRIGHTNESSCAM_ABC_IO_SERVICE_H
