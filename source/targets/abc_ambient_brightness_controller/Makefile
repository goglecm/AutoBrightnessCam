#######################
# General definitions #
#######################

include ../Common.in

ABC_AMBIENT_BRIGHTNESS_CONTROLLER_BUILD_PATH = $(BUILD_PATH)/src/abc_ambient_brightness_controller

ABC_AMBIENT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \

include $(SOURCE_PATH)/src/abc_ambient_brightness_controller/Makefile.in

##########################
# Add -I and -L prefixes #
##########################

ABC_AMBIENT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $(ABC_AMBIENT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
abc_ambient_brightness_controller_clean \
abc_ambient_brightness_controller_build \

abc_ambient_brightness_controller_clean:
	cd $(ABC_AMBIENT_BRIGHTNESS_CONTROLLER_BUILD_PATH); \
	rm -rf ./*.o

abc_ambient_brightness_controller_build:
	make -j abc_ambient_brightness_controller_clean
	cd $(ABC_AMBIENT_BRIGHTNESS_CONTROLLER_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(ABC_AMBIENT_BRIGHTNESS_CONTROLLER_SOURCES) \
	$(ABC_AMBIENT_BRIGHTNESS_CONTROLLER_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \
