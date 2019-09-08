#include "abc_filter/abc_filter.h"

#include "abc_logging_service/abc_logging_service.h"

typedef abc_filter_AveragerData_t AveragerData_t;

bool
abc_filter_average(AveragerData_t *const restrict pFilter,
                   const double nextSample,
                   double *const restrict pAverage)
{
    if (!(pFilter && pAverage))
    {
        ABC_LOG_ERR("bad pFilter(%p) or pAverage(%p)", (void *)pFilter, (void *)pAverage);

        return false;
    }

    const unsigned fSize = pFilter->SIZE;

    if (fSize == 0)
    {
        ABC_LOG_ERR("filter size is 0");

        return false;
    }

    if (pFilter->internal_pos >= fSize)
    {
        ABC_LOG_ERR("filter position (%u) beyond filter size (%u)", pFilter->internal_pos, fSize);

        return false;
    }

    // Write value into the filter at current position.
    pFilter->pValues[pFilter->internal_pos] = nextSample;

    ABC_LOG("values[%u] = %f", pFilter->internal_pos, nextSample);

    // Advance to to the next position.
    ++pFilter->internal_pos;
    if (pFilter->internal_pos >= fSize)
    {
        pFilter->internal_pos = 0;
    }

    // Calculate the average.
    double runningAverage = 0;
    {
        const double *const restrict pValues = pFilter->pValues;
        for (unsigned i = 0; i < fSize; ++i)
        {
            runningAverage += pValues[i];
        }
    }
    runningAverage /= fSize;

    ABC_LOG("final avg = %f", runningAverage);

    *pAverage = runningAverage;

    return true;
}
