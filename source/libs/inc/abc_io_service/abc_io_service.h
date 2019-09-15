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

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_IO_SERVICE_H
