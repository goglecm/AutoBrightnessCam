


########################################################################
#                                                                      #
#                          ### WARNING ###                             #
#                                                                      #
# Internal build infrastructure, refer to the Makefile for the targets #
#                                                                      #
########################################################################


##################
# Path shortcuts #
##################

MODULE_TARGETS_PATH = $(TARGETS_PATH)/$(MODULE_NAME)

MODULE_SOURCE_PATH = $(SOURCE_PATH)/src/$(MODULE_NAME)

MODULE_SOURCE_INC_PATH = $(SOURCE_PATH)/inc/$(MODULE_NAME)

MODULE_FAKES_SOURCE_PATH = $(SOURCE_PATH)/src_test/$(MODULE_NAME)

MODULE_TESTS_SOURCE_PATH = $(SOURCE_PATH)/tests/$(MODULE_NAME)

MODULE_FAKES_SOURCE_INC_PATH = $(SOURCE_PATH)/inc_test/$(MODULE_NAME)

MODULE_BUILD_PATH = $(BUILD_PATH)/src/$(MODULE_NAME)

MODULE_FAKES_BUILD_PATH = $(BUILD_PATH)/src_test/$(MODULE_NAME)

MODULE_TESTS_BUILD_PATH = $(BUILD_PATH)/tests/$(MODULE_NAME)

##################
# Module sources #
##################

MODULE_SOURCES_WITH_PATH = $(wildcard $(MODULE_SOURCE_PATH)/*.c)
MODULE_HEADERS_WITH_PATH = $(wildcard $(MODULE_SOURCE_INC_PATH)/*.h)

MODULE_SOURCES_WITHOUT_PATH = $(foreach var, $(MODULE_SOURCES_WITH_PATH), $(notdir $(var)))
MODULE_HEADERS_WITHOUT_PATH = $(foreach var, $(MODULE_HEADERS_WITH_PATH), $(notdir $(var)))

##################
# Module objects #
##################

MODULE_OBJECTS_WITHOUT_PATH = $(foreach var, $(MODULE_SOURCES_WITHOUT_PATH), $(subst .c,.o,$(var)))

MODULE_OBJECTS_WITH_PATH = $(foreach var, $(MODULE_OBJECTS_WITHOUT_PATH), $(MODULE_BUILD_PATH)/$(var))

#######################
# Module fake sources #
#######################

MODULE_FAKE_SOURCES_WITH_PATH = $(wildcard $(MODULE_FAKES_SOURCE_PATH)/*.c)
MODULE_FAKE_HEADERS_WITH_PATH = $(wildcard $(MODULE_FAKES_SOURCE_INC_PATH)/*.h)

MODULE_FAKE_SOURCES_WITHOUT_PATH = $(foreach var, $(MODULE_FAKE_SOURCES_WITH_PATH), $(notdir $(var)))
MODULE_FAKE_HEADERS_WITHOUT_PATH = $(foreach var, $(MODULE_FAKE_HEADERS_WITHOUT_PATH), $(notdir $(var)))

#######################
# Module fake objects #
#######################

MODULE_FAKE_OBJECTS_WITHOUT_PATH = $(foreach var, $(MODULE_FAKE_SOURCES_WITHOUT_PATH), $(subst .c,.o,$(var)))
MODULE_FAKE_OBJECTS_WITH_PATH = $(foreach var, $(MODULE_FAKE_OBJECTS_WITHOUT_PATH), $(MODULE_FAKES_BUILD_PATH)/$(var))

#######################
# Module test sources #
#######################

MODULE_TEST_SOURCES = $(MODULE_TESTS_SOURCE_PATH)/*.cpp

##################
# Target aliases #
##################

MODULE_STATIC_LIB_WITH_PATH = $(MODULE_BUILD_PATH)/lib$(MODULE_NAME).a

MODULE_EXE_WITH_PATH = $(MODULE_BUILD_PATH)/$(MODULE_NAME).exe

MODULE_TEST_EXE_WITH_PATH = $(MODULE_TESTS_BUILD_PATH)/test_$(MODULE_NAME).exe

###########
# Targets #
###########

.PHONY: \
clean_module \
clean_fakes \
clean_tests \
clean_logs \
clean \
tests_run \
build_deps \

#
# Cleaning
#
clean_logs :
	cd $(ABC_LOGGING_PATH); \
		rm -f *$(MODULE_NAME)*.log

clean_module :
	cd $(MODULE_BUILD_PATH); \
		rm -rf *.o *.a *.exe *.log

clean_fakes :
	cd $(MODULE_FAKES_BUILD_PATH); \
		rm -rf *.o *.a *.exe *.log

clean_tests :
	cd $(MODULE_TESTS_BUILD_PATH); \
		rm -rf *.o *.a *.exe *.out *.jpeg *.log

clean : clean_module clean_fakes clean_tests clean_logs

#
# Run tests
#
tests_run :
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(DYNAMIC_LIBS_PATH); \
		$(MODULE_TEST_EXE_WITH_PATH) | tee $(ABC_LOGGING_PATH)/$(MODULE_NAME)_run_log.log \

#
# Build the current module' sources only (as .o files)
#
$(MODULE_OBJECTS_WITH_PATH) : $(MODULE_SOURCES_WITH_PATH) $(MODULE_HEADERS_WITH_PATH)
	$(CC) -fPIC -c \
		$(MODULE_SOURCE_PATH)/$(subst .o,.c,$(notdir $@)) \
		$(MODULE_MASTER_INC_PATH_PREFIXED) \
		$(C_FLAGS) \
		-o $@

#
# Build the static libraries of all dependencies
#
build_deps :
	for dep in $($(MODULE_NAME)_DEPENDENCIES) ; do \
		make -f $(TARGETS_PATH)/$$dep/Makefile $(BUILD_PATH)/src/$$dep/lib$$dep.a ;\
	done

#
# Build the module static library (.a file) which will include the dependencies
# as well
#
$(MODULE_STATIC_LIB_WITH_PATH) : build_deps $(MODULE_OBJECTS_WITH_PATH)
	$(foreach dep, \
		$($(MODULE_NAME)_DEPENDENCIES), \
			cd $(MODULE_BUILD_PATH); \
				$(AR) x $(BUILD_PATH)/src/$(dep)/lib$(dep).a; )

	$(AR) rcs $(MODULE_BUILD_PATH)/lib$(MODULE_NAME).a \
		$(MODULE_BUILD_PATH)/*.o

#
# Build an executable from the module
# Only for modules which define the main function
#
$(MODULE_EXE_WITH_PATH) : $(MODULE_STATIC_LIB_WITH_PATH)
	$(CC) $(MODULE_BUILD_PATH)/*.a $(C_FLAGS) -o $@

#
# Build the current module' fake dependencies only (as .o files)
#
$(MODULE_FAKE_OBJECTS_WITH_PATH) : $(MODULE_FAKE_SOURCES_WITH_PATH) $(MODULE_FAKE_HEADERS_WITH_PATH)
	$(CC) -fPIC -c \
		$(MODULE_FAKES_SOURCE_PATH)/$(subst .o,.c,$(notdir $@)) \
		$(MODULE_MASTER_INC_PATH_PREFIXED) \
		$(C_FLAGS) \
		-o $@

#
# Build the test sources and test executable for the current module
# Include the logging service here explicitly
#
$(MODULE_TEST_EXE_WITH_PATH) : $(MODULE_FAKE_OBJECTS_WITH_PATH) $(MODULE_OBJECTS_WITH_PATH) $(MODULE_TEST_SOURCES)
	make -f $(TARGETS_PATH)/abc_logging_service/Makefile $(PARALLEL_FLAG) \
		$(BUILD_PATH)/src/abc_logging_service/libabc_logging_service.a

	$(CXX) \
		$(MODULE_BUILD_PATH)/*.o \
		$(MODULE_FAKES_BUILD_PATH)/*.o \
		$(MODULE_TEST_SOURCES) \
		$(BUILD_PATH)/src/abc_logging_service/*.a \
		$(MODULE_MASTER_INC_PATH_PREFIXED) \
		$(DYNAMIC_LIBS) \
		$(LIBS_INC_DIR) \
		$(CXX_FLAGS) \
		-o $@ \
