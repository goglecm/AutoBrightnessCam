#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_FILTER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

bool
fake_abc_filter_areAllFilterStatesEqualAndNonZero(void);

unsigned
fake_abc_filter_getNumAverageCalls(void);

void
fake_abc_filter_resetNumAverageCalls(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_FILTER_H
