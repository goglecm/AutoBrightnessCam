#######################
# General definitions #
#######################

CC=gcc
CXX=g++
AR=ar

SOURCE_PATH = /home/john/CLionProjects/AutoBrightnessCam/source
BUILD_PATH = /home/john/CLionProjects/AutoBrightnessCam/build
LIBS_PATH = /home/john/CLionProjects/AutoBrightnessCam/libs
TARGETS_PATH = /home/john/CLionProjects/AutoBrightnessCam/source/targets

#########
# Flags #
#########

C_WARNING_FLAGS = \
	-Wall \
	-Wpedantic \
	-Wextra \
	-Werror \

C_MISC_FLAGS = \
	-std=gnu99

C_OPTIMISATION_FLAGS = \
	-O3 \
	-g0 \

C_FLAGS = \
	$(C_WARNING_FLAGS) \
	$(C_MISC_FLAGS) \
	$(C_OPTIMISATION_FLAGS) \

CXX_WARNING_FLAGS = \
	-Wall \
	-Wextra \
	-Werror \

CXX_OPTIMISATION_FLAGS = \
	-O3 \
	-g0 \

CXX_FLAGS = \
	$(CXX_WARNING_FLAGS) \
	$(CXX_OPTIMISATION_FLAGS) \

#############
# Libraries #
#############

COMMON_INC_PATH += \
	$(LIBS_PATH)/google-test/googletest-release-1.7.0/include \

DYNAMIC_LIBS_PATH = \
	$(LIBS_PATH)/google-test/googletest-release-1.7.0/ \

DYNAMIC_LIBS = \
	-lgtest \
	-lgtest_main \

##########################
# Add -I and -L prefixes #
##########################

DYNAMIC_LIBS_PATH_PREFIXED = \
	$(foreach var, $(DYNAMIC_LIBS_PATH), -L$(var))

include ../CommonTargets.mk
