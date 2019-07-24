


###############################################################
# Contains the shortcut targets needed to:                    #
# - clean and build any modules                               #
# - clean, build and run the tests of any modules             #
# - clean, build and run the tests of all modules in parallel #
# - build the main application                                #
###############################################################




PARALLEL_FLAG = -j

ifdef NUM_CORES_TO_USE
PARALLEL_FLAG = -j$(NUM_CORES_TO_USE)
endif

ALL_MODULES = \
	main \
	abc_time_service \
	abc_io_service \
	abc_terminal_controller \
	abc_logging_service \
	abc_brightness_service \
	abc_power_controller \
	abc_backlight_brightness_controller \
	abc_ambient_brightness_controller \

# Do not include abc_logging_service
MODULES_TO_TEST = \
	abc_io_service \
	abc_terminal_controller \
	abc_brightness_service \
	abc_power_controller \
	abc_backlight_brightness_controller \
	abc_ambient_brightness_controller \
	abc_logging_service \

#################
# BUILD AND RUN #
#################

## Target to clean, build and run all tests from all modules (and build mains)
all:
	make $(PARALLEL_FLAG) clean

	make $(PARALLEL_FLAG) build_all_mains

	make $(PARALLEL_FLAG) clean

	make $(PARALLEL_FLAG) build_all_tests

	make $(PARALLEL_FLAG) run_tests

############
# CLEANING #
############

MODULES_TO_CLEAN_TARGETS = \
	$(foreach var, $(ALL_MODULES), clean_$(var))

$(MODULES_TO_CLEAN_TARGETS):
	make -f $(subst clean_,,$@)/Makefile $(PARALLEL_FLAG) module_clean_all

## Target to clean everything
clean:
	rm -f ./*.test ./*.exe
	make $(PARALLEL_FLAG) $(MODULES_TO_CLEAN_TARGETS)

########
# MAIN #
########

## Target to build the main application with logging on
build_main_with_logs:
	ABC_LOGGING_ON=1 make -f main/Makefile $(PARALLEL_FLAG) module_exe_build

## Target to build the main application with logging off
build_main_without_logs:
	ABC_LOGGING_ON=0 make -f main/Makefile $(PARALLEL_FLAG) module_exe_build

## Target to build the main application (with and without logging) with the
## former available at the end of the recipe
build_all_mains:
	make $(PARALLEL_FLAG) build_main_with_logs
	make $(PARALLEL_FLAG) build_main_without_logs

#########
# BUILD #
#########

MODULES_TO_BUILD_TEST_TARGETS = \
	$(foreach var, $(MODULES_TO_TEST), testbuild_$(var))

MODULES_TO_BUILD_TARGETS = \
	$(foreach var, $(ALL_MODULES), build_$(var))

## Target to build individual modules for testing. The targets are:
## testbuild_abc_module, where module is the module
$(MODULES_TO_BUILD_TEST_TARGETS):
	make -f $(subst testbuild_,,$@)/Makefile -j module_tests_build

## Target to build individual modules for production. The targets are:
## build_abc_module, where module is the module
$(MODULES_TO_BUILD_TARGETS):
	make -f $(subst build_,,$@)/Makefile $(PARALLEL_FLAG) module_build_with_deps

## Target to build all modules for testing
build_all_tests:
	make $(PARALLEL_FLAG) clean

	make $(PARALLEL_FLAG) $(MODULES_TO_BUILD_TEST_TARGETS)

## Target to build all modules for production
build_all_modules:
	make $(PARALLEL_FLAG) clean

	make $(PARALLEL_FLAG) $(MODULES_TO_BUILD_TARGETS)

#############
# RUN TESTS #
#############

MODULES_TO_RUN_TEST_TARGETS = \
	$(foreach var, $(MODULES_TO_TEST), testrun_$(var))

$(MODULES_TO_RUN_TEST_TARGETS):
	make -f $(subst testrun_,,$@)/Makefile $(PARALLEL_FLAG) module_tests_run

## Target to run all tests from all modules (assuming everything is built)
run_tests:
	make $(PARALLEL_FLAG) $(MODULES_TO_RUN_TEST_TARGETS)

.PHONY: \
	all \
	clean \
	build_all_mains \
	build_all_modules \
	build_all_tests \
	build_main_basic \
	run_tests \
	$(MODULES_TO_RUN_TEST_TARGETS) \
	$(MODULES_TO_BUILD_TARGETS) \
	$(MODULES_TO_BUILD_TEST_TARGETS) \
	$(MODULES_TO_CLEAN_TARGETS) \
