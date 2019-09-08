#ifndef AUTOBRIGHTNESSCAM_ABC_FILTER_H
#define AUTOBRIGHTNESSCAM_ABC_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct abc_filter_AveragerData_t
{
    const unsigned SIZE; // Filter size

    double *const pValues; // Filter state

    unsigned internal_pos; // Index in the filter state where the next sample is written

} abc_filter_AveragerData_t;

bool
abc_filter_average(abc_filter_AveragerData_t *pFilter,
                   double nextSample,
                   double *pAverage);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_FILTER_H
