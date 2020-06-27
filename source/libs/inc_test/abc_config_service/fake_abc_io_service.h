#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

void
fake_abc_ioService_setConfigEntry(const char *pEntryStr);

void
fake_abc_ioService_setDefaultConfigEntry(const char *pEntryStr);

void
fake_abc_ioService_failToFindLine(void);

#ifdef __cplusplus
}
#endif

#endif // AUTOBRIGHTNESSCAM_FAKE_ABC_IO_SERVICE_H
