#ifndef AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
#define AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    FAKE_ABC_BACKLIGHT_BRIGHTNESS_NOT_SET,
    FAKE_ABC_BACKLIGHT_BRIGHTNESS_SET

} fake_abc_BacklightBrightnessStatus_t;

typedef struct
{
    fake_abc_BacklightBrightnessStatus_t set;

    double value;

} fake_abc_BacklightBrightnessValue_t;

fake_abc_BacklightBrightnessValue_t
fake_abc_backlightBrightnessController_get(void);

unsigned
fake_abc_backlightBrightnessController_numSetCalls(void);

void
fake_abc_backlightBrightnessController_resetNumSetCalls(void);

#ifdef __cplusplus
}
#endif

#endif //AUTOBRIGHTNESSCAM_FAKE_ABC_TERMINAL_CONTROLLER_H
