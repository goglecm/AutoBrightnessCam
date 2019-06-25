#include "abc_brightness_service.h"

#include <unistd.h>

#include <stdio.h>

int main(void)
{
    abc_brightnessService_setPeriod(5);

    abc_brightnessService_start();

    do
    {
        printf("sleeping 1 sec\n");

        sleep(1);
    }
    while (abc_brightnessService_wakeUp() == abc_brightnessService_SUCCESS);

    return -1;
}
