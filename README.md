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

Run production:
*MODULE_NAME=main make -f ~/source/targets/main/Makefile -j exe_build*

Run tests on the abc_brightness module (or any other module):
*MODULE_NAME=abc_brightness_service make -f ~/source/targets/abc_brightness_service/Makefile -j run_tests*

### Background

The build system works around the concept of a module. Each module has a set of 
dependencies (dependant modules) defined in the Makefile of the respective 
module.

The Makefile for module, say abc_brightness_service is located at:
~/source/targets/abc_brightness_service/Makefile

Variable $(MODULE_NAME) should be defined prior to making any target.

For instance, to build the abc_brightness_service module:

*MODULE_NAME=abc_brightness_service make -f ~/source/targets/abc_brightness_service/Makefile build_with_deps*

### Build targets

**build_no_deps** - cleans the module build area and builds the .o object files 
of the module

**build_with_deps** - cleans the module build area, builds the .o object 
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
