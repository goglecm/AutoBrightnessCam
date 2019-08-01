#ifndef AUTOBRIGHTNESSCAM_ABC_FILTER_H
#define AUTOBRIGHTNESSCAM_ABC_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <stdint.h>

typedef struct abc_filter_AveragerData_t
{
    const uint16_t SIZE; // Filter size

    uint16_t *const pValues; // Filter state

    uint16_t internal_pos; // Index in the filter state where the next sample is written

} abc_filter_AveragerData_t;

bool
abc_filter_average(abc_filter_AveragerData_t *pFilter,
                   uint16_t nextSample,
                   uint16_t *pAverage);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_FILTER_H
