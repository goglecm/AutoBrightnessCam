#ifndef AUTOBRIGHTNESSCAM_ABC_UTILS_H
#define AUTOBRIGHTNESSCAM_ABC_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Preceding/trailing whitespace may not always be tolerated.
bool
abc_utils_strToInt(int *pResult, const char *pStr);

#ifdef __cplusplus
}
#endif


#endif //AUTOBRIGHTNESSCAM_ABC_UTILS_H
