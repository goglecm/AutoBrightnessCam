ABC_TEST_LDLIBS = \
	libabc_test.la \
	libabc_logging_service_active.la \
	-lgtest \
	-lgtest_main \
	-lpthread

# la libraries come first, then follow the -l ones.

test_abc_ambient_controller_LDADD                       = $(ABC_TEST_LDLIBS)
test_abc_backlight_controller_LDADD                     = $(ABC_TEST_LDLIBS)
test_abc_logging_service_LDADD                          = libabc_test.la -lgtest -lgtest_main -lpthread
test_abc_brightness_service_LDADD                       = $(ABC_TEST_LDLIBS)
test_abc_brightness_service_fake_abc_time_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_filter_LDADD                                   = $(ABC_TEST_LDLIBS)
test_abc_io_service_LDADD                               = libabc_utils.la $(ABC_TEST_LDLIBS) # No need to fake the abc_utils module.
test_abc_utils_LDADD                                    = $(ABC_TEST_LDLIBS)
test_abc_config_service_libconfig_LDADD                 = $(ABC_TEST_LDLIBS) $(LIBCONFIG_LIBS)
test_abc_power_controller_LDADD                         = $(ABC_TEST_LDLIBS)
test_abc_power_controller_upower_LDADD                  = $(ABC_TEST_LDLIBS)
test_abc_terminal_controller_LDADD                      = $(ABC_TEST_LDLIBS)

test_abc_ambient_controller_CPPFLAGS                       = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_backlight_controller_CPPFLAGS                     = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_logging_service_CPPFLAGS                          = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_brightness_service_CPPFLAGS                       = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_brightness_service_fake_abc_time_service_CPPFLAGS = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_filter_CPPFLAGS                                   = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_io_service_CPPFLAGS                               = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_utils_CPPFLAGS                                    = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_config_service_libconfig_CPPFLAGS                 = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1 $(LIBCONFIG_CFLAGS)
test_abc_power_controller_CPPFLAGS                         = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=0
test_abc_power_controller_upower_CPPFLAGS                  = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_terminal_controller_CPPFLAGS                      = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1

test_abc_ambient_controller_CFLAGS                       = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_backlight_controller_CFLAGS                     = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_logging_service_CFLAGS                          = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_brightness_service_CFLAGS                       = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_brightness_service_fake_abc_time_service_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_filter_CFLAGS                                   = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_io_service_CFLAGS                               = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_utils_CFLAGS                                    = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_config_service_libconfig_CFLAGS                 = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1 $(LIBCONFIG_CFLAGS)
test_abc_power_controller_CFLAGS                         = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=0
test_abc_power_controller_upower_CFLAGS                  = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_terminal_controller_CFLAGS                      = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1


test_abc_ambient_controller_SOURCES = \
	$(libabc_ambient_controller_la_SOURCES) \
	libs/src_test/abc_ambient_controller/fake_abc_terminal_controller.c \
	libs/tests/abc_ambient_controller/tests_abc_ambient_controller.cpp \
	libs/inc_test/abc_ambient_controller/fake_abc_terminal_controller.h

test_abc_backlight_controller_SOURCES = \
	$(libabc_backlight_controller_la_SOURCES) \
	libs/tests/abc_backlight_controller/tests_abc_backlight_controller.cpp \
	libs/src_test/abc_backlight_controller/fake_abc_io_service.c \
	libs/src_test/abc_backlight_controller/fake_abc_time_service.c \
	libs/inc_test/abc_backlight_controller/fake_abc_io_service.h

test_abc_logging_service_SOURCES = \
	$(libabc_logging_service_la_SOURCES) \
	libs/tests/abc_logging_service/tests_abc_logging_service.cpp

test_abc_brightness_service_SOURCES = \
	$(libabc_brightness_service_la_SOURCES) \
	libs/tests/abc_brightness_service/tests_abc_brightness_service.cpp \
	libs/src_test/abc_brightness_service/fake_abc_ambient_controller.c \
	libs/src_test/abc_brightness_service/fake_abc_backlight_controller.c \
	libs/src_test/abc_brightness_service/fake_abc_filter.c \
	libs/src_test/abc_brightness_service/fake_abc_power_controller.c \
	libs/src_test/abc_brightness_service/fake_abc_time_service.c \
	libs/inc_test/abc_brightness_service/fake_abc_ambient_controller.h \
	libs/inc_test/abc_brightness_service/fake_abc_backlight_controller.h \
	libs/inc_test/abc_brightness_service/fake_abc_filter.h \
	libs/inc_test/abc_brightness_service/fake_abc_power_controller.h \
	libs/inc_test/abc_brightness_service/fake_abc_time_service.h

test_abc_brightness_service_fake_abc_time_service_SOURCES = \
	libs/tests/abc_brightness_service/tests_fake_abc_time_service.cpp \
	libs/src_test/abc_brightness_service/fake_abc_time_service.c

test_abc_filter_SOURCES = \
	$(libabc_filter_la_SOURCES) \
	libs/tests/abc_filter/tests_abc_filter.cpp

test_abc_io_service_SOURCES = \
	$(libabc_io_service_la_SOURCES) \
	libs/tests/abc_io_service/tests_abc_io_service.cpp

test_abc_utils_SOURCES = \
	$(libabc_utils_la_SOURCES) \
	libs/tests/abc_utils/tests_abc_utils.cpp

test_abc_config_service_libconfig_SOURCES = \
	$(libabc_config_service_la_libconfig_sources) \
	libs/tests/abc_config_service/tests_abc_config_service_libconfig.cpp

test_abc_power_controller_SOURCES = \
	$(libabc_power_controller_la_SOURCES) \
	libs/tests/abc_power_controller/tests_abc_power_controller.cpp \
	libs/inc_test/abc_power_controller/fake_abc_io_service.h \
	libs/src_test/abc_power_controller/fake_abc_io_service.c

test_abc_power_controller_upower_SOURCES = \
	$(libabc_power_controller_la_SOURCES) \
	libs/tests/abc_power_controller/tests_abc_power_controller.cpp \
	libs/inc_test/abc_power_controller/fake_abc_terminal_controller.h \
	libs/src_test/abc_power_controller/fake_abc_terminal_controller.c

test_abc_terminal_controller_SOURCES = \
	$(libabc_terminal_controller_la_SOURCES) \
	libs/tests/abc_terminal_controller/tests_abc_terminal_controller.cpp

