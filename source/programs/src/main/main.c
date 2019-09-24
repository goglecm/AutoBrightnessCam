#include "abc_brightness_service/abc_brightness_service.h"

#include <stdlib.h>
#include <argp.h>
#include <unistd.h>

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include <config.h>
#endif // #ifndef CONFIG_H_INCLUDED

const char *argp_program_version     = PACKAGE_STRING;
const char *argp_program_bug_address = "<" PACKAGE_BUGREPORT ">";

static const char doc[] =
    "App to automatically adjust the display brightness using the luminosity "
    "information from the webcam. To start it, simply pass no arguments.";

static struct argp argp = { .doc = doc };

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        argp_parse(&argp, argc, argv, 0, 0, 0);

        exit(0);
    }
    else
    {
        abc_brightnessService_setPeriod(10);

        abc_brightnessService_start();

        do
        {
            sleep(10);
        }
        while (abc_brightnessService_wakeUp() == ABC_BRIGHTNESSSERVICE_SUCCESS);

        return -1;
    }
}
