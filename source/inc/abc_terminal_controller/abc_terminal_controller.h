#ifndef AUTOBRIGHTNESSCAM_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


// Return true on success.

bool
abc_terminalController_send(unsigned resultLen,
                            char *pResult,
                            const char *pCmd);

bool
abc_terminalController_writeFile(int value, const char *pFileName);

bool
abc_terminalController_readFile(int *pValue, const char *pFileName);

bool
abc_terminalController_readCmdDouble(double *pValue, const char *pCmd);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_ABC_TERMINAL_CONTROLLER_H
