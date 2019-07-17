#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

uint16_t
fake_abc_ioService_getCurrentBrightness(void);

unsigned
fake_abc_ioService_getNumWrites(void);

void
fake_abc_ioService_resetNumWriteCalls(void);

void
fake_abc_ioService_setMaxBrightness(uint16_t value);

void
fake_abc_ioService_failReads(bool isReadFail);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H
