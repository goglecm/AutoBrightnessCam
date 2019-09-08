#include "abc_brightness_service/abc_brightness_service.h"

#include <unistd.h>

#include <stdio.h>

#include <config.h>

int main(void)
{
    abc_brightnessService_setPeriod(4);

    abc_brightnessService_start();

#ifdef ABC_TEST_123
	printf("Good\n");
#else
	printf("Bad\n");
#endif

    do
    {
        sleep(4);
    }
    while (abc_brightnessService_wakeUp() == ABC_BRIGHTNESSSERVICE_SUCCESS);

    return -1;
}
