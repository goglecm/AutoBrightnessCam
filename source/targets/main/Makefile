#######################
# General definitions #
#######################

include ../Common.in

MAIN_BUILD_PATH = $(BUILD_PATH)/src/main

MAIN_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \

include $(SOURCE_PATH)/src/main/Makefile.in

include $(TARGETS_PATH)/abc_ambient_brightness_controller/Makefile
include $(TARGETS_PATH)/abc_backlight_brightness_controller/Makefile
include $(TARGETS_PATH)/abc_brightness_service/Makefile
include $(TARGETS_PATH)/abc_power_controller/Makefile
include $(TARGETS_PATH)/abc_time_service/Makefile

##########################
# Add -I and -L prefixes #
##########################

MAIN_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $(MAIN_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
main_clean \
main_build \

main_clean:
	cd $(MAIN_BUILD_PATH); \
	rm -rf ./*.o

main_build:
	make -j main_clean
	cd $(MAIN_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(MAIN_SOURCES) \
	$(MAIN_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \

full_main_build:
	make -j \
		abc_brightness_service_build \
		abc_backlight_brightness_controller_build \
		abc_ambient_brightness_controller_build \
		abc_power_controller_build \
		abc_time_service_build \
		main_build
	cd $(MAIN_BUILD_PATH); \
	$(CC) \
	$(ABC_BRIGHTNESS_SERVICE_BUILD_PATH)/*.o \
	$(ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_BUILD_PATH)/*.o \
	$(ABC_AMBIENT_BRIGHTNESS_CONTROLLER_BUILD_PATH)/*.o \
	$(ABC_POWER_CONTROLLER_BUILD_PATH)/*.o \
	$(ABC_TIME_SERVICE_BUILD_PATH)/*.o \
	$(MAIN_BUILD_PATH)/*.o \
	$(MAIN_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \
	-o main.exe; \
