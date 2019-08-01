#include "abc_filter/abc_filter.h"

#include "abc_logging_service/abc_logging_service.h"

typedef abc_filter_AveragerData_t AveragerData_t;

bool
abc_filter_average(AveragerData_t *const pFilter,
                   const uint16_t nextSample,
                   uint16_t *const pAverage)
{
    if (!(pFilter && pAverage))
    {
        ABC_LOG_ERR("bad pFilter(%p) or pAverage(%p)", (void *)pFilter, (void *)pAverage);

        return false;
    }

    if (pFilter->SIZE == 0)
    {
        ABC_LOG_ERR("filter size is 0");

        return false;
    }

    if (pFilter->internal_pos >= pFilter->SIZE)
    {
        ABC_LOG_ERR("filter position (%u) beyond filter size (%u)", pFilter->internal_pos, pFilter->SIZE);

        return false;
    }

    // Write value into the filter at current position.
    pFilter->pValues[pFilter->internal_pos] = nextSample;

    ABC_LOG("values[%u] = %u", pFilter->internal_pos, nextSample);

    // Advance to to the next position.
    ++pFilter->internal_pos;
    if (pFilter->internal_pos >= pFilter->SIZE)
    {
        pFilter->internal_pos = 0;
    }

    // Calculate the average.
    uint32_t runningAverage = 0;
    for (uint16_t i = 0; i < pFilter->SIZE; ++i)
    {
        runningAverage += pFilter->pValues[i];
    }
    runningAverage /= pFilter->SIZE;

    ABC_LOG("final avg = %u", runningAverage);

    *pAverage = (uint16_t)runningAverage;

    return true;
}
