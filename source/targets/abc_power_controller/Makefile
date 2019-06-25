#######################
# General definitions #
#######################

include ../Common.in

ABC_POWER_CONTROLLER_BUILD_PATH = $(BUILD_PATH)/src/abc_power_controller

ABC_POWER_CONTROLLER_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \

include $(SOURCE_PATH)/src/abc_power_controller/Makefile.in

##########################
# Add -I and -L prefixes #
##########################

ABC_POWER_CONTROLLER_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $(ABC_POWER_CONTROLLER_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
abc_power_controller_clean \
abc_power_controller_build \

abc_power_controller_clean:
	cd $(ABC_POWER_CONTROLLER_BUILD_PATH); \
	rm -rf ./*.o

abc_power_controller_build:
	make -j abc_power_controller_clean
	cd $(ABC_POWER_CONTROLLER_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(ABC_POWER_CONTROLLER_SOURCES) \
	$(ABC_POWER_CONTROLLER_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \
