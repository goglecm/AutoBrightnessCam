# AutoBrightnessCam

App to periodically set the appropriate brightness of a laptop display backlight 
according to the ambient luminosity using a laptop camera.

Note: The ~ is defined as the root of the project in this README.

## Project paths

There are 3 paths at the root of the project:

**~/source** - contains all projects source code along with the Makefiles

**~/libs** - contains the source code and dynamic libraries for any external 
libraries used (which are not needed for production)

**~/build** - contains all the objects, archives, executable and other 
build/runtime files

### Source

**~/source/inc** - contains the module API headers

**~/source/inc_test** - contains the test API headers of the interfaces the 
module uses to interact with its dependencies

**~/source/src** - contains the *production* sources implementing the module API 
headers. There may be multiple of these directories possibly providing a 
different module implementation.

**~/source/src_test** - contains the implementation of the test API headers. 
Again, there may be multiple of these directories to provide alternative 
implementations.

**~/source/targets** - contains the Makefile of each module (describing its 
dependencies)

**~/source/tests** - contains the google-test sources, which have tests for each 
module

### Build

Same mapping as the source, except these directories hold build files.

## How To build

### TL;DR

Clean, run all tests and build important targets:

`make -f ~/source/targets/Makefile run_all_tests`

Run production:

`MODULE_NAME=main make -f ~/source/targets/main/Makefile -j exe_build`

then (with sudo) run the main exe:

`sudo ~/build/src/main/main.exe`

Other useful targets:

Run tests on the abc_brightness module (or any other module):

`make -f ~/source/targets/Makefile -j clean_abc_brightness_service`
`make -f ~/source/targets/Makefile -j test_abc_brightness_service`
`make -f ~/source/targets/Makefile -j testrun_abc_brightness_service`

Enable/disable logging:

`ABC_LOGGING_ON=1 make ...`

### Background

The build system works around the concept of a module. Each module has a set of 
dependencies (dependant modules) defined in the Makefile of the respective 
module.

The Makefile for module, say abc_brightness_service is located at:
~/source/targets/abc_brightness_service/Makefile

Variable $(MODULE_NAME) should be defined prior to making any target.

For instance, to build the abc_brightness_service module:

`MODULE_NAME=abc_brightness_service make -f ~/source/targets/abc_brightness_service/Makefile build_with_deps`

### Build targets 

#### Global targets

These targets are defined in ~/source/targets/Makefile

**run_all_tests** - builds a couple of versions of main, runs
the tests for the logging module and then runs the tests of
all other modules

**run_all** - runs the tests of all modules except for the
logging module

**build_all_tests** - builds all modules and links them
against the test dependencies. This produces the *.exe which
when run, runs the tests for that module

**build_main** - builds a couple of versions of main

**clean** - purges the build area

Individual modules can also be manipulated from here:

**clean_abc_module** - cleans the module called abc_module

**test_abc_module** - builds the module called abc_module and
links it with the test dependencies

**testrun_abc_module** - runs the tests for the module 
called abc_module

#### Targets per module

These targets are defined in ~/source/targets/CommonTargets.mk

**build_no_deps** - builds the .o object files 
of the module

**build_with_deps** - builds the .o object 
files of the module, does a *build_with_deps* on each of its dependant modules 
and links all these into a .a archive file

**exe_build** - does a *build_with_deps* on the module and links the .a archive 
to create a .exe executable file, which can be run. This is only useful for 
modules defining a *main()* function.

**tests_build** - does a *build_no_deps*, a build of the fakes (the interface 
used by the test to interact with the module), a build of the tests and then
links these to create a test .exe executable

**tests_run** - does a *tests_build* and then runs the tests

**clean_all** - cleans all the build files of the module
