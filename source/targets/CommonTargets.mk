PARALLEL_FLAG = -j

ifdef NUM_CORES_TO_USE
PARALLEL_FLAG = -j$(NUM_CORES_TO_USE)
endif

$(MODULE_NAME)_MODULE_BUILD_PATH = $(BUILD_PATH)/src/$(MODULE_NAME)

$(MODULE_NAME)_MODULE_FAKES_BUILD_PATH = $(BUILD_PATH)/src_test/$(MODULE_NAME)

$(MODULE_NAME)_MODULE_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \
	$(SOURCE_PATH)/inc \
	$(SOURCE_PATH)/inc_test \

$(MODULE_NAME)_MODULE_SOURCES = $(SOURCE_PATH)/src/$(MODULE_NAME)/*.c

$(MODULE_NAME)_MODULE_FAKES_SOURCES = $(SOURCE_PATH)/src_test/$(MODULE_NAME)/*.c

$(MODULE_NAME)_TEST_SOURCES = $(SOURCE_PATH)/tests/$(MODULE_NAME)/*.cpp

ifndef ABC_LOGGING_ON
ABC_LOGGING_ON = 1
endif

C_FLAGS += -DABC_LOGGING_ON=$(ABC_LOGGING_ON)

CXX_FLAGS += -DABC_LOGGING_ON=$(ABC_LOGGING_ON)

##########################
# Add -I and -L prefixes #
##########################

$(MODULE_NAME)_MODULE_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $($(MODULE_NAME)_MODULE_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
clean \
build_no_deps \
build_with_deps \
fakes_clean \
fakes_build \
tests_clean \
tests_run \
clean_all

clean:
	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		rm -rf *.o *.a *.exe

fakes_clean:
	cd $($(MODULE_NAME)_MODULE_FAKES_BUILD_PATH); \
		rm -rf *.o *.a *.exe

clean_all:
	MODULE_NAME=$(MODULE_NAME) make $(PARALLEL_FLAG) clean fakes_clean tests_clean

build_no_deps:
	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		$(CC) -fPIC -c \
			$($(MODULE_NAME)_MODULE_SOURCES) \
			$($(MODULE_NAME)_MODULE_MASTER_INC_PATH_PREFIXED) \
			$(C_FLAGS)

build_with_deps:
	cd $(TARGETS_PATH)/$(MODULE_NAME); \
		MODULE_NAME=$(MODULE_NAME) make $(PARALLEL_FLAG) build_no_deps

	$(foreach dep, \
		$($(MODULE_NAME)_DEPENDENCIES), \
		MODULE_NAME=$(dep) \
			make -f $(TARGETS_PATH)/$(dep)/Makefile $(PARALLEL_FLAG) build_with_deps;)

	$(foreach dep, \
		$($(MODULE_NAME)_DEPENDENCIES), \
		cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
			ar x $(BUILD_PATH)/src/$(dep)/*.a; )

	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		$(AR) rcs lib$(MODULE_NAME).a \
			$($(MODULE_NAME)_MODULE_BUILD_PATH)/*.o \

exe_build:
	MODULE_NAME=$(MODULE_NAME) make $(PARALLEL_FLAG) build_with_deps

	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		$(CC) \
			$($(MODULE_NAME)_MODULE_BUILD_PATH)/*.a \
			$(C_FLAGS) \
			-o $(MODULE_NAME).exe; \

fakes_build:
	cd $($(MODULE_NAME)_MODULE_FAKES_BUILD_PATH); \
		$(CC) -fPIC -c \
		$($(MODULE_NAME)_MODULE_FAKES_SOURCES) \
		$($(MODULE_NAME)_MODULE_MASTER_INC_PATH_PREFIXED) \
		$(C_FLAGS) \

tests_clean:
	cd $($(MODULE_NAME)_MODULE_TESTS_BUILD_PATH); \
		rm -rf *.o *.a *.exe *.out *.jpeg

# Include the logging service here explicitly

tests_build:
	MODULE_NAME=$(MODULE_NAME) make $(PARALLEL_FLAG) \
		build_no_deps \
		fakes_build \

	cd ../abc_logging_service; \
	MODULE_NAME=abc_logging_service make $(PARALLEL_FLAG) build_with_deps

	cd $($(MODULE_NAME)_MODULE_TESTS_BUILD_PATH); \
		$(CXX) \
		$($(MODULE_NAME)_MODULE_BUILD_PATH)/*.o \
		$($(MODULE_NAME)_MODULE_FAKES_BUILD_PATH)/*.o \
		$($(MODULE_NAME)_TEST_SOURCES) \
		$(BUILD_PATH)/src/abc_logging_service/*.a \
		$($(MODULE_NAME)_MODULE_MASTER_INC_PATH_PREFIXED) \
		$(DYNAMIC_LIBS_PATH_PREFIXED) \
		$(DYNAMIC_LIBS) \
		$(LIBS_INC_DIR) \
		$(CXX_FLAGS) \
		-o test_$(MODULE_NAME).exe; \

tests_run:
	cd $($(MODULE_NAME)_MODULE_TESTS_BUILD_PATH); \
		export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(DYNAMIC_LIBS_PATH); \
		./test_$(MODULE_NAME).exe \
