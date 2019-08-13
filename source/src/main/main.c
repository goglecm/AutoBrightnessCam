#include "abc_brightness_service/abc_brightness_service.h"

int main(void)
{
    unsigned wakeups = 50;

    abc_brightnessService_setPeriod(1);

    abc_brightnessService_start();

    do
    {
        --wakeups;

        if (wakeups == 0)
        {
            break;
        }
    }
    while (abc_brightnessService_wakeUp() == ABC_BRIGHTNESSSERVICE_SUCCESS);

    return 0;
}
