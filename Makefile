


###############################################################
# Contains the shortcut targets needed to:                    #
# - clean and build any modules                               #
# - clean, build and run the tests of any modules             #
# - clean, build and run the tests of all modules in parallel #
# - build the main application                                #
###############################################################

PROJ_DIR = $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

PARALLEL_FLAG = -j

NUM_CORES_TO_USE = 8

ifdef NUM_CORES_TO_USE
PARALLEL_FLAG = -j$(NUM_CORES_TO_USE)
endif

MAKE = PROJ_DIR=$(PROJ_DIR) NUM_CORES_TO_USE=$(NUM_CORES_TO_USE) PARALLEL_FLAG=$(PARALLEL_FLAG) make

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
	abc_filter \

MODULES_TO_TEST = \
	abc_io_service \
	abc_terminal_controller \
	abc_brightness_service \
	abc_power_controller \
	abc_backlight_brightness_controller \
	abc_ambient_brightness_controller \
	abc_filter \
	abc_logging_service \

#################
# BUILD AND RUN #
#################

## Target to clean, build and run all tests from all modules (and build mains)
all :
	$(MAKE) clean

	$(MAKE) build_all_mains

	$(MAKE) clean

	$(MAKE) build_all_tests

	$(MAKE) run_tests

	$(MAKE) check_test_results

check_test_results:
	@echo
	@echo =============
	@echo = Failures: =
	@echo =============
	@echo
	@cat $(PROJ_DIR)/build/logs/*run_log.log | grep "FAILED\|Failure\|Value of: \|Actual: \|Expected: \|Which is: " | cat

############
# CLEANING #
############

MODULES_TO_CLEAN_TARGETS = $(ALL_MODULES)

$(MODULES_TO_CLEAN_TARGETS) :
	$(MAKE) -f $(PROJ_DIR)/source/targets/$(subst clean_,,$@)/Makefile clean

## Target to clean everything
clean :
	rm -f $(PROJ_DIR)/run/*.test
	rm -f $(PROJ_DIR)/build/logs/*.log
	$(MAKE) $(PARALLEL_FLAG) $(MODULES_TO_CLEAN_TARGETS)

########
# MAIN #
########

## Target to build the main application with logging on
build_main_with_logs :
	ABC_LOGGING_ON=1 $(MAKE) -f $(PROJ_DIR)/source/targets/main/Makefile \
		$(PROJ_DIR)/build/src/main/main.exe

## Target to build the main application with logging off
build_main_without_logs :
	ABC_LOGGING_ON=0 $(MAKE) -f $(PROJ_DIR)/source/targets/main/Makefile \
		$(PROJ_DIR)/build/src/main/main.exe

## Target to build the main application (with and without logging) with the
## former available at the end of the recipe
build_all_mains :
	$(MAKE) build_main_with_logs
	$(MAKE) build_main_without_logs

#########
# BUILD #
#########

MODULES_TO_BUILD_TEST_TARGETS = \
	$(foreach var, $(MODULES_TO_TEST), testbuild_$(var))

MODULES_TO_BUILD_TARGETS = \
	$(foreach var, $(ALL_MODULES), build_$(var))

## Target to build individual modules for testing. The targets are:
## testbuild_abc_module, where module is the module
$(MODULES_TO_BUILD_TEST_TARGETS) :
	$(MAKE) -f $(PROJ_DIR)/source/targets/$(subst testbuild_,,$@)/Makefile \
		$(PROJ_DIR)/build/tests/$(subst testbuild_,,$@)/test_$(subst testbuild_,,$@).exe

## Target to build individual modules for production. The targets are:
## build_abc_module, where module is the module
$(MODULES_TO_BUILD_TARGETS) :
	$(MAKE) -f $(PROJ_DIR)/source/targets/$(subst build_,,$@)/Makefile \
		$(PROJ_DIR)/build/src/$(subst build_,,$@)/test_$(subst build_,,$@).exe

## Target to build all modules for testing
build_all_tests :
	$(MAKE) $(PARALLEL_FLAG) $(MODULES_TO_BUILD_TEST_TARGETS)

## Target to build all modules for production
build_all_modules :
	$(MAKE) $(MODULES_TO_BUILD_TARGETS)

#############
# RUN TESTS #
#############

MODULES_TO_RUN_TEST_TARGETS = \
	$(foreach var, $(MODULES_TO_TEST), testrun_$(var))

$(MODULES_TO_RUN_TEST_TARGETS) :
	$(MAKE) -f $(PROJ_DIR)/source/targets/$(subst testrun_,,$@)/Makefile tests_run

## Target to run all tests from all modules (assuming everything is built)
run_tests :
	$(MAKE) $(PARALLEL_FLAG) $(MODULES_TO_RUN_TEST_TARGETS)

.PHONY: \
	all \
	check_test_results \
	clean \
	$(MODULES_TO_CLEAN_TARGETS) \
	build_all_mains \
	build_all_modules \
	build_all_tests \
	build_main_basic \
	run_tests \
	$(MODULES_TO_RUN_TEST_TARGETS) \
	$(MODULES_TO_BUILD_TARGETS) \
	$(MODULES_TO_BUILD_TEST_TARGETS) \
