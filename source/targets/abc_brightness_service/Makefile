#######################
# General definitions #
#######################

include ../Common.in

ABC_BRIGHTNESS_SERVICE_BUILD_PATH = $(BUILD_PATH)/src/abc_brightness_service
ABC_BRIGHTNESS_SERVICE_FAKES_BUILD_PATH = $(BUILD_PATH)/src_test/abc_brightness_service

ABC_BRIGHTNESS_SERVICE_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \

include $(SOURCE_PATH)/src/abc_brightness_service/Makefile.in
include $(SOURCE_PATH)/src_test/abc_brightness_service/Makefile.in
include $(SOURCE_PATH)/tests/abc_brightness_service/Makefile.in

##########################
# Add -I and -L prefixes #
##########################

ABC_BRIGHTNESS_SERVICE_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $(ABC_BRIGHTNESS_SERVICE_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
abc_brightness_service_clean \
abc_brightness_service_build \
abc_brightness_service_fakes_clean \
abc_brightness_service_fakes_build \
abc_brightness_service_tests_clean \
abc_brightness_service_tests_run

abc_brightness_service_clean:
	cd $(ABC_BRIGHTNESS_SERVICE_BUILD_PATH); \
	rm -rf ./*.o

abc_brightness_service_fakes_clean:
	cd $(ABC_BRIGHTNESS_SERVICE_FAKES_BUILD_PATH); \
	rm -rf ./*.o

abc_brightness_service_build:
	make -j abc_brightness_service_clean
	cd $(ABC_BRIGHTNESS_SERVICE_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(ABC_BRIGHTNESS_SERVICE_SOURCES) \
	$(ABC_BRIGHTNESS_SERVICE_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \

abc_brightness_service_fakes_build:
	make -j abc_brightness_service_fakes_clean
	cd $(ABC_BRIGHTNESS_SERVICE_FAKES_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(ABC_BRIGHTNESS_SERVICE_FAKES_SOURCES) \
	$(ABC_BRIGHTNESS_SERVICE_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \

abc_brightness_service_tests_clean:
	cd $(ABC_BRIGHTNESS_SERVICE_TESTS_BUILD_PATH); \
	rm -rf *.exe \
	rm -rf *.out \
	rm -rf *.jpeg \

tests_build:
	make -j \
		abc_brightness_service_build \
		abc_brightness_service_fakes_build \
		abc_brightness_service_tests_clean
	cd $(ABC_BRIGHTNESS_SERVICE_TESTS_BUILD_PATH); \
	$(CXX) \
	$(ABC_BRIGHTNESS_SERVICE_BUILD_PATH)/*.o \
	$(ABC_BRIGHTNESS_SERVICE_FAKES_BUILD_PATH)/*.o \
	$(TEST_SOURCES) \
	$(ABC_BRIGHTNESS_SERVICE_MASTER_INC_PATH_PREFIXED) \
	$(DYNAMIC_LIBS_PATH_PREFIXED) \
	$(DYNAMIC_LIBS) \
	$(LIBS_INC_DIR) \
	$(CXX_FLAGS) \
	-o test.exe; \

abc_brightness_service_tests_run:
	make tests_build
	cd $(ABC_BRIGHTNESS_SERVICE_TESTS_BUILD_PATH); \
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(DYNAMIC_LIBS_PATH); \
	./test.exe \
