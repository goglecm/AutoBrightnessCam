


########################################################################
#                                                                      #
#                          ### WARNING ###                             #
#                                                                      #
# Internal build infrastructure, refer to the Makefile for the targets #
#                                                                      #
########################################################################



$(MODULE_NAME)_MODULE_BUILD_PATH = $(BUILD_PATH)/src/$(MODULE_NAME)

$(MODULE_NAME)_MODULE_FAKES_BUILD_PATH = $(BUILD_PATH)/src_test/$(MODULE_NAME)

$(MODULE_NAME)_MODULE_TESTS_BUILD_PATH = $(BUILD_PATH)/tests/$(MODULE_NAME)

$(MODULE_NAME)_MODULE_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \
	$(SOURCE_PATH)/inc \
	$(SOURCE_PATH)/inc_test \

$(MODULE_NAME)_MODULE_SOURCES = $(SOURCE_PATH)/src/$(MODULE_NAME)/*.c

$(MODULE_NAME)_MODULE_FAKES_SOURCES = $(SOURCE_PATH)/src_test/$(MODULE_NAME)/*.c

$(MODULE_NAME)_TEST_SOURCES = $(SOURCE_PATH)/tests/$(MODULE_NAME)/*.cpp

###################
# Add -I prefixes #
###################

$(MODULE_NAME)_MODULE_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $($(MODULE_NAME)_MODULE_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
module_clean \
module_clean_logs \
module_clean_fakes \
module_clean_tests \
module_clean_all \
module_build_with_deps \
module_tests_run \

module_clean_logs:
	cd $(ABC_LOGGING_PATH); \
		rm -f *$(MODULE_NAME)*.log

module_clean:
	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		rm -rf *.o *.a *.exe *.log

module_clean_fakes:
	cd $($(MODULE_NAME)_MODULE_FAKES_BUILD_PATH); \
		rm -rf *.o *.a *.exe *.log

module_clean_all:
	make -f $(MODULE_NAME)/Makefile $(PARALLEL_FLAG) \
		module_clean \
		module_clean_fakes \
		module_clean_tests \
		module_clean_logs

module_clean_tests:
	cd $($(MODULE_NAME)_MODULE_TESTS_BUILD_PATH); \
		rm -rf *.o *.a *.exe *.out *.jpeg *.log

module_build_no_deps : $($(MODULE_NAME)_MODULE_SOURCES)
	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		$(CC) -fPIC -c \
			$($(MODULE_NAME)_MODULE_SOURCES) \
			$($(MODULE_NAME)_MODULE_MASTER_INC_PATH_PREFIXED) \
			$(C_FLAGS)

module_build_with_deps:
	make -f $(TARGETS_PATH)/$(MODULE_NAME)/Makefile $(PARALLEL_FLAG) \
		module_build_no_deps

	$(foreach dep, \
		$($(MODULE_NAME)_DEPENDENCIES), \
			make -f $(TARGETS_PATH)/$(dep)/Makefile $(PARALLEL_FLAG) \
				module_build_with_deps;)

	$(foreach dep, \
		$($(MODULE_NAME)_DEPENDENCIES), \
			cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
				ar x $(BUILD_PATH)/src/$(dep)/*.a; )

	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		$(AR) rcs lib$(MODULE_NAME).a \
			$($(MODULE_NAME)_MODULE_BUILD_PATH)/*.o \

module_exe_build:
	make -f $(MODULE_NAME)/Makefile $(PARALLEL_FLAG) \
		module_build_with_deps

	cd $($(MODULE_NAME)_MODULE_BUILD_PATH); \
		$(CC) \
			$($(MODULE_NAME)_MODULE_BUILD_PATH)/*.a \
			$(C_FLAGS) \
			-o $(MODULE_NAME).exe; \

module_fakes_build : $($(MODULE_NAME)_MODULE_FAKES_SOURCES)
	cd $($(MODULE_NAME)_MODULE_FAKES_BUILD_PATH); \
		$(CC) -fPIC -c \
		$($(MODULE_NAME)_MODULE_FAKES_SOURCES) \
		$($(MODULE_NAME)_MODULE_MASTER_INC_PATH_PREFIXED) \
		$(C_FLAGS) \

# Include the logging service here explicitly

module_tests_build:
	make -f $(MODULE_NAME)/Makefile $(PARALLEL_FLAG) \
		module_build_no_deps \
		module_fakes_build \

	make -f $(TARGETS_PATH)/abc_logging_service/Makefile $(PARALLEL_FLAG) module_build_with_deps

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

module_tests_run :
	cd $($(MODULE_NAME)_MODULE_TESTS_BUILD_PATH); \
		export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(DYNAMIC_LIBS_PATH); \
		./test_$(MODULE_NAME).exe | tee $(ABC_LOGGING_PATH)/$(MODULE_NAME)_run_log.log \
