#include "abc_brightness_service/abc_brightness_service.h"

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    abc_brightnessService_setPeriod(5);

    abc_brightnessService_start();

    do
    {
        printf("sleeping 1 sec\n");

        sleep(1);
    }
    while (abc_brightnessService_wakeUp() == ABC_BRIGHTNESSSERVICE_SUCCESS);

    return -1;
}
