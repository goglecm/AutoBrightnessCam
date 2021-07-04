#
# Library dependencies (no recursive dependencies allowed)
#
libabc_filter_la_LIBADD              = libabc_logging_service.la
libabc_utils_la_LIBADD               = libabc_logging_service.la
libabc_terminal_controller_la_LIBADD = libabc_logging_service.la
libabc_time_service_la_LIBADD        = libabc_logging_service.la
libabc_power_controller_la_LIBADD    = libabc_logging_service.la

if ABC_USES_UPOWER

libabc_power_controller_la_LIBADD += libabc_terminal_controller.la

else

libabc_power_controller_la_LIBADD += libabc_io_service.la

endif # if ABC_USES_UPOWER

libabc_ambient_controller_la_LIBADD = \
	libabc_terminal_controller.la \
	libabc_logging_service.la

libabc_backlight_controller_la_LIBADD = \
	libabc_logging_service.la \
	libabc_io_service.la \
	libabc_time_service.la

libabc_brightness_service_la_LIBADD = \
	libabc_power_controller.la \
	libabc_ambient_controller.la \
	libabc_backlight_controller.la \
	libabc_time_service.la \
	libabc_logging_service.la \
	libabc_filter.la

libabc_config_service_la_LIBADD = \
	libabc_logging_service.la

libabc_config_service_la_LIBADD += \
	$(LIBCONFIG_LIBS)

libabc_io_service_la_LIBADD = \
	libabc_logging_service.la \
	libabc_utils.la


#
# Libraries build flags
#
LIB_FLAGS = \
	$(GENERAL_DEFINITIONS) \
	$(GENERAL_INCLUDE_PATHS) \
	$(C_WARNING_FLAGS) \
	$(C_STANDARD)

libabc_ambient_controller_la_CFLAGS   = $(LIB_FLAGS)
libabc_backlight_controller_la_CFLAGS = $(LIB_FLAGS)
libabc_brightness_service_la_CFLAGS   = $(LIB_FLAGS)
libabc_filter_la_CFLAGS               = $(LIB_FLAGS)
libabc_io_service_la_CFLAGS           = $(LIB_FLAGS)
libabc_logging_service_la_CFLAGS      = $(LIB_FLAGS)
libabc_power_controller_la_CFLAGS     = $(LIB_FLAGS)
libabc_terminal_controller_la_CFLAGS  = $(LIB_FLAGS)
libabc_time_service_la_CFLAGS         = $(LIB_FLAGS)
libabc_config_service_la_CFLAGS       = $(LIB_FLAGS) $(LIBCONFIG_CFLAGS)
libabc_utils_la_CFLAGS                = $(LIB_FLAGS)


#
# Library sources
#
libabc_ambient_controller_la_SOURCES   = libs/src/abc_ambient_controller/abc_ambient_controller.c
libabc_backlight_controller_la_SOURCES = libs/src/abc_backlight_controller/abc_backlight_controller.c
libabc_brightness_service_la_SOURCES   = libs/src/abc_brightness_service/abc_brightness_service.c
libabc_filter_la_SOURCES               = libs/src/abc_filter/abc_filter.c
libabc_io_service_la_SOURCES           = libs/src/abc_io_service/abc_io_service.c
libabc_logging_service_la_SOURCES      = libs/src/abc_logging_service/abc_logging_service.c
libabc_power_controller_la_SOURCES     = libs/src/abc_power_controller/abc_power_controller.c
libabc_terminal_controller_la_SOURCES  = libs/src/abc_terminal_controller/abc_terminal_controller.c
libabc_time_service_la_SOURCES         = libs/src/abc_time_service/abc_time_service.c
libabc_utils_la_SOURCES                = libs/src/abc_utils/abc_utils.c

libabc_config_service_la_libconfig_sources = \
	libs/src/abc_config_service/abc_config_service_libconfig.c \
	libs/src/abc_config_service/abc_config_service.c

libabc_config_service_la_SOURCES = \
	$(libabc_config_service_la_libconfig_sources)


#
# Library headers
#
libabc_ambient_controller_la_SOURCES   += libs/inc/abc_ambient_controller/abc_ambient_controller.h
libabc_backlight_controller_la_SOURCES += libs/inc/abc_backlight_controller/abc_backlight_controller.h
libabc_brightness_service_la_SOURCES   += libs/inc/abc_brightness_service/abc_brightness_service.h
libabc_filter_la_SOURCES               += libs/inc/abc_filter/abc_filter.h
libabc_io_service_la_SOURCES           += libs/inc/abc_io_service/abc_io_service.h
libabc_logging_service_la_SOURCES      += libs/inc/abc_logging_service/abc_logging_service.h
libabc_power_controller_la_SOURCES     += libs/inc/abc_power_controller/abc_power_controller.h
libabc_terminal_controller_la_SOURCES  += libs/inc/abc_terminal_controller/abc_terminal_controller.h
libabc_time_service_la_SOURCES         += libs/inc/abc_time_service/abc_time_service.h
libabc_utils_la_SOURCES                += libs/inc/abc_utils/abc_utils.h
libabc_config_service_la_SOURCES       += \
	libs/inc/abc_config_service/abc_config_service.h \
	libs/src/abc_config_service/abc_config_service_common.h
