#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Sets the return string returned by abc_terminalController_sendReturnStr.
// NOTE: The pRetVal string is NOT copied, but merely stored. After being used,
// the copied pointer is replaced with a NULL internally. Make sure to keep the
// pointer in scope until after all the necessary
// abc_terminalController_sendReturnStr calls have been made.
//
// isCount - is this an entry count string or an entry value
// isDefault - is this string from the default config or from the host config
void
fake_abc_terminalController_setReturnStr(
        const char *pRetVal,
        bool isDefault,
        bool isCount);

#ifdef __cplusplus
}
#endif

#endif // AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
