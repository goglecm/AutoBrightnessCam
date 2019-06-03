#######################
# General definitions #
#######################

CC=gcc
CXX=g++

SOURCE_PATH = /home/john/CLionProjects/AutoBrightnessCam/source
BUILD_PATH = /home/john/CLionProjects/AutoBrightnessCam/build
LIBS_PATH = /home/john/CLionProjects/AutoBrightnessCam/libs

PROJECT_BUILD_PATH = $(BUILD_PATH)/src
TEST_BUILD_PATH = $(BUILD_PATH)/tests

MASTER_INCLUDE_PATH = $(SOURCE_PATH)

include src/Makefile.in
include tests/Makefile.in

##########################
# Add -I and -L prefixes #
##########################

MASTER_INCLUDE_PATH_PREFIXED = \
	$(foreach var, $(MASTER_INCLUDE_PATH), -I$(var))

DYNAMIC_LIBS_PATH_PREFIXED = \
	$(foreach var, $(DYNAMIC_LIBS_PATH), -L$(var))

#########
# Flags #
#########

C_WARNING_FLAGS = \
	-Wall \
	-Wpedantic \
	-Wextra \
	-Werror \

C_MISC_FLAGS = \
	-std=c99

C_OPTIMISATION_FLAGS = \
	-Os \

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

CXX_FLAGS = \
	$(CXX_WARNING_FLAGS) \
	$(CXX_OPTIMISATION_FLAGS) \

###########
# Targets #
###########

.PHONY: project_clean project_build tests_clean tests_run

project_clean:
	cd $(PROJECT_BUILD_PATH); \
	rm -rf ./*.o

project_build:
	make -j project_clean
	cd $(PROJECT_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(PROJECT_SOURCES) \
	$(MASTER_INCLUDE_PATH_PREFIXED) \
	$(C_FLAGS) \

tests_clean:
	cd $(TEST_BUILD_PATH); \
	rm -rf *.exe \
	rm -rf *.out \

tests_build:
	make -j project_build tests_clean
	cd $(TEST_BUILD_PATH); \
	$(CXX) \
	$(PROJECT_BUILD_PATH)/*.o \
	$(TEST_SOURCES) \
	$(MASTER_INCLUDE_PATH_PREFIXED) \
	$(DYNAMIC_LIBS_PATH_PREFIXED) \
	$(DYNAMIC_LIBS) \
	$(LIBS_INC_DIR) \
	$(CXX_FLAGS) \
	-o test.exe; \

tests_run:
	make tests_build
	cd $(TEST_BUILD_PATH); \
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(DYNAMIC_LIBS_PATH); \
	./test.exe \
