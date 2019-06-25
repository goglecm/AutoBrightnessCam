#######################
# General definitions #
#######################

include ../Common.in

ABC_TIME_SERVICE_BUILD_PATH = $(BUILD_PATH)/src/abc_time_service

ABC_TIME_SERVICE_MASTER_INC_PATH += \
	$(SOURCE_PATH) \
	$(COMMON_INC_PATH) \

include $(SOURCE_PATH)/src/abc_time_service/Makefile.in

##########################
# Add -I and -L prefixes #
##########################

ABC_TIME_SERVICE_MASTER_INC_PATH_PREFIXED = \
	$(foreach var, $(ABC_TIME_SERVICE_MASTER_INC_PATH), -I$(var))

###########
# Targets #
###########

.PHONY: \
abc_time_service_clean \
abc_time_service_build \

abc_time_service_clean:
	cd $(ABC_TIME_SERVICE_BUILD_PATH); \
	rm -rf ./*.o

abc_time_service_build:
	make -j abc_time_service_clean
	cd $(ABC_TIME_SERVICE_BUILD_PATH); \
	$(CC) -fPIC -c \
	$(ABC_TIME_SERVICE_SOURCES) \
	$(ABC_TIME_SERVICE_MASTER_INC_PATH_PREFIXED) \
	$(C_FLAGS) \
