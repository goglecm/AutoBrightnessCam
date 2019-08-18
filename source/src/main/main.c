#include "abc_brightness_service/abc_brightness_service.h"

#include <unistd.h>

int main(void)
{
    abc_brightnessService_setPeriod(4);

    abc_brightnessService_start();

    do
    {
        sleep(4);
    }
    while (abc_brightnessService_wakeUp() == ABC_BRIGHTNESSSERVICE_SUCCESS);

    return -1;
}
