aubrca_LDADD = \
	libabc_brightness_service.la \
	libabc_backlight_controller.la \
	libabc_config_service.la \
	libabc_logging_service.la


if ABC_USES_UPOWER

aubrca_LDADD += libabc_power_controller.la

endif # ABC_USES_UPOWER


aubrca_SOURCES = programs/src/main/main.c
