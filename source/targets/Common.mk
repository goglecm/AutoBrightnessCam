


########################################################################
#                                                                      #
#                          ### WARNING ###                             #
#                                                                      #
# Internal build infrastructure, refer to the Makefile for the targets #
#                                                                      #
########################################################################




#######################
# General definitions #
#######################

ifndef ABC_LOGGING_ON
ABC_LOGGING_ON = 1
endif

ifndef ABC_STDOUT_LOGGING_ON
ABC_STDOUT_LOGGING_ON = 0
endif

CC=gcc
CXX=g++
AR=ar


SOURCE_PATH = $(PROJ_DIR)/source
BUILD_PATH = $(PROJ_DIR)/build
LIBS_PATH = $(PROJ_DIR)/libs
RUN_PATH = $(PROJ_DIR)/run
TARGETS_PATH = $(SOURCE_PATH)/targets

ABC_LOGGING_PATH = $(BUILD_PATH)/logs

#########
# Flags #
#########

C_WARNING_FLAGS += -Wall
C_WARNING_FLAGS += -Wpedantic
C_WARNING_FLAGS += -Wextra
C_WARNING_FLAGS += -Werror
C_WARNING_FLAGS += -Wno-unknown-warning
C_WARNING_FLAGS += -Wdouble-promotion
C_WARNING_FLAGS += -Wformat-y2k
C_WARNING_FLAGS += -Wmissing-include-dirs
C_WARNING_FLAGS += -Wswitch-default
C_WARNING_FLAGS += -Wunused-parameter
C_WARNING_FLAGS += -Wstrict-aliasing
C_WARNING_FLAGS += -Wstrict-overflow=5
C_WARNING_FLAGS += -Wtrampolines
C_WARNING_FLAGS += -Wfloat-equal
C_WARNING_FLAGS += -Wshadow
C_WARNING_FLAGS += -Wpointer-arith
C_WARNING_FLAGS += -Wbad-function-cast
C_WARNING_FLAGS += -Wc++-compat
C_WARNING_FLAGS += -Wcast-qual
C_WARNING_FLAGS += -Wcast-align
C_WARNING_FLAGS += -Wwrite-strings
C_WARNING_FLAGS += -Wconversion -Wno-sign-conversion
C_WARNING_FLAGS += -Wjump-misses-init
C_WARNING_FLAGS += -Wlogical-op
C_WARNING_FLAGS += -Wstrict-prototypes
C_WARNING_FLAGS += -Wold-style-definition
C_WARNING_FLAGS += -Wmissing-declarations
C_WARNING_FLAGS += -Wredundant-decls
C_WARNING_FLAGS += -Wnested-externs
C_WARNING_FLAGS += -Wunsuffixed-float-constants
C_WARNING_FLAGS += -Wunsafe-loop-optimizations

C_MISC_FLAGS = \
	-std=gnu99

C_OPTIMISATION_FLAGS = \
	-O3 \
	-g0 \
	-fstrict-aliasing \
	-fstrict-overflow \
	-fmodulo-sched \
	-fmodulo-sched-allow-regmoves \
	-fgcse-lm -fgcse-sm -fgcse-las -fgcse-after-reload \
	-funsafe-loop-optimizations \
	-fipa-pta \
	-fgraphite-identity \
	-floop-flatten \
	-ftree-loop-if-convert \
	-ftree-loop-if-convert-stores \
	-ftree-loop-distribution \
	-funroll-loops \
	-freorder-blocks-and-partition \
	-ffast-math \
	-fno-signed-zeros \

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

C_FLAGS += -DABC_LOGGING_ON=$(ABC_LOGGING_ON)

CXX_FLAGS += -DABC_LOGGING_ON=$(ABC_LOGGING_ON)

C_FLAGS += -DABC_LOGGING_PATH=\"$(ABC_LOGGING_PATH)\"

C_FLAGS += -DABC_TESTRUN_PATH=\"$(RUN_PATH)\"

CXX_FLAGS += -DABC_LOGGING_PATH=\"$(ABC_LOGGING_PATH)\"

CXX_FLAGS += -DABC_TESTRUN_PATH=\"$(RUN_PATH)\"

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

###################
# Add -L prefixes #
###################

DYNAMIC_LIBS_PATH_PREFIXED = \
	$(foreach var, $(DYNAMIC_LIBS_PATH), -L$(var))

#######################
# Header search paths #
#######################

MODULE_MASTER_INC_PATH = \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \
	$(SOURCE_PATH)/inc \
	$(SOURCE_PATH)/inc_test \

MODULE_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $(MODULE_MASTER_INC_PATH), -I$(var))


include $(TARGETS_PATH)/CommonTargets.mk
