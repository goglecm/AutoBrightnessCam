PARALLEL_FLAG = -j

ifdef NUM_CORES_TO_USE
PARALLEL_FLAG = -j$(NUM_CORES_TO_USE)
endif

MODULES_TO_CLEAN = \
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

############
# CLEANING #
############

MODULES_TO_CLEAN_TARGETS = \
	$(foreach var, $(MODULES_TO_CLEAN), clean_$(var))

$(MODULES_TO_CLEAN_TARGETS):
	cd ./$(subst clean_,,$@); \
		MODULE_NAME=$(subst clean_,,$@) make -f Makefile $(PARALLEL_FLAG) clean_all

clean:
	make $(PARALLEL_FLAG) $(MODULES_TO_CLEAN_TARGETS)

########
# MAIN #
########

build_main:
	# Build main (with logs)
	make $(PARALLEL_FLAG) clean
	cd ./main; \
		MODULE_NAME=main ABC_LOGGING_ON=1 make -f Makefile $(PARALLEL_FLAG) exe_build

	# Build main (no logs)
	make -j clean
	cd ./main; \
		MODULE_NAME=main ABC_LOGGING_ON=0 make -f Makefile $(PARALLEL_FLAG) exe_build

#########
# BUILD #
#########

MODULES_TO_BUILD_TEST_TARGETS = \
	$(foreach var, $(MODULES_TO_TEST), test_$(var))

$(MODULES_TO_BUILD_TEST_TARGETS):
	cd ./$(subst test_,,$@); \
		MODULE_NAME=$(subst test_,,$@) make -f Makefile -j tests_build

build_all_tests:
	make $(PARALLEL_FLAG) clean

	make $(PARALLEL_FLAG) $(MODULES_TO_BUILD_TEST_TARGETS)

#############
# RUN TESTS #
#############

MODULES_TO_RUN_TEST_TARGETS = \
	$(foreach var, $(MODULES_TO_TEST), testrun_$(var))

$(MODULES_TO_RUN_TEST_TARGETS):
	cd ./$(subst testrun_,,$@); \
		MODULE_NAME=$(subst testrun_,,$@) make -f Makefile $(PARALLEL_FLAG) tests_run

run_all:
	make $(PARALLEL_FLAG) $(MODULES_TO_RUN_TEST_TARGETS)

#################
# BUILD AND RUN #
#################

run_all_tests:

	make $(PARALLEL_FLAG) clean

	cd ./abc_logging_service; \
		MODULE_NAME=abc_logging_service make -f Makefile $(PARALLEL_FLAG) tests_build

	cd ./abc_logging_service; \
		MODULE_NAME=abc_logging_service make -f Makefile $(PARALLEL_FLAG) tests_run

	make $(PARALLEL_FLAG) build_main

	make $(PARALLEL_FLAG) build_all_tests

	make $(PARALLEL_FLAG) run_all
