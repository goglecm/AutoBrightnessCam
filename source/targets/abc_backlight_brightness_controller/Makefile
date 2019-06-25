#######################
# General definitions #
#######################

include ../Common.in

ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_BUILD_PATH = $(BUILD_PATH)/src/abc_backlight_brightness_controller

ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \

include $(SOURCE_PATH)/src/abc_backlight_brightness_controller/Makefile.in

##########################
# Add -I and -L prefixes #
##########################

ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $(ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
abc_backlight_brightness_controller_clean \
abc_backlight_brightness_controller_build \

abc_backlight_brightness_controller_clean:
	cd $(ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_BUILD_PATH); \
	rm -rf ./*.o

abc_backlight_brightness_controller_build:
	make -j abc_backlight_brightness_controller_clean
	cd $(ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_SOURCES) \
	$(ABC_BACKLIGHT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \
