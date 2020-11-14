#include "abc_filter/abc_filter.h"
#include "abc_brightness_service/fake_abc_filter.h"

#include <assert.h>
#include <math.h>

static unsigned
s_numAverageCalls;

static abc_filter_AveragerData_t
*pTestFilter;

unsigned
fake_abc_filter_getNumAverageCalls(void)
{
    return s_numAverageCalls;
}

bool
fake_abc_filter_areAllFilterStatesEqualAndNonZero(void)
{
    assert(pTestFilter);

    assert(pTestFilter->SIZE && pTestFilter->pValues);

    // Check if the values are non-zero.
    if (pTestFilter->pValues[0] < (double)0.0001F)
    {
        return false;
    }

    // Check if the states are the same.
    for (unsigned i = 0; i < pTestFilter->SIZE - 1; ++i)
    {
        const double diff = fabs(pTestFilter->pValues[i] - pTestFilter->pValues[i + 1]);

        if (diff > (double)0.1F)
        {
            return false;
        }
    }

    return true;
}

void
fake_abc_filter_resetNumAverageCalls(void)
{
    s_numAverageCalls = 0;
}

bool
abc_filter_average(abc_filter_AveragerData_t *const restrict pFilter,
                   const double nextSample,
                   double *const restrict pAverage)
{
    (void)nextSample;

    assert(pFilter && pAverage);

    pTestFilter = pFilter;

    ++s_numAverageCalls;

    return true;
}
