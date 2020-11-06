#
# Warning flags
#
C_WARNING_FLAGS = \
	-Wall \
	-Wpedantic \
	-Wextra \
	-Wno-unknown-warning \
	-Wno-unknown-warning-option \
	-Wdouble-promotion \
	-Wformat-y2k \
	-Wmissing-include-dirs \
	-Wswitch-default \
	-Wunused-parameter \
	-Wstrict-aliasing \
	-Wstrict-overflow=5 \
	-Wtrampolines \
	-Wfloat-equal \
	-Wshadow \
	-Wpointer-arith \
	-Wbad-function-cast \
	-Wc++-compat \
	-Wcast-qual \
	-Wcast-align \
	-Wwrite-strings \
	-Wconversion \
	-Wno-sign-conversion \
	-Wjump-misses-init \
	-Wlogical-op \
	-Wstrict-prototypes \
	-Wold-style-definition \
	-Wmissing-declarations \
	-Wredundant-decls \
	-Wnested-externs \
	-Wunsuffixed-float-constants \
	-Wunsafe-loop-optimizations


#
# Definitions
#
if ABC_USES_UPOWER

GENERAL_DEFINITIONS = -DABC_HAS_UPOWER=1

else

GENERAL_DEFINITIONS = -DABC_HAS_UPOWER=0

endif # if ABC_USES_UPOWER


GENERAL_DEFINITIONS += \
	-DABC_PICTURE_DIR=\"$(localstatedir)/aubrca\" \
	-DABC_CONFIG_FILENAME=\"$(sysconfdir)/aubrca.conf\" \
	-DABC_CONFIG_DEFAULTS_FILENAME=\"$(datadir)/aubrca/defaults.conf\"


if ABC_USES_DEBUG

GENERAL_DEFINITIONS += \
	-DDEBUG=1 \
	-DABC_LOGGING_ON=1 \
	-DABC_LOGGING_DEFAULT_FILENAME=\"$(localstatedir)/aubrca/debug.log\"

else

GENERAL_DEFINITIONS += -DNDEBUG=1 -DABC_LOGGING_ON=0

endif # if ABC_USES_DEBUG


#
# Global build flags
#
AM_CFLAGS = \
	$(GENERAL_DEFINITIONS) \
	-std=gnu99 $(C_WARNING_FLAGS) \
	-I$(top_srcdir)/source/libs/inc


#
# Libraries (not to be installed)
#
noinst_LTLIBRARIES = libabc_ambient_controller.la \
					 libabc_backlight_controller.la \
					 libabc_brightness_service.la \
					 libabc_filter.la \
					 libabc_io_service.la \
					 libabc_logging_service.la \
					 libabc_power_controller.la \
					 libabc_terminal_controller.la \
					 libabc_time_service.la \
					 libabc_config_service.la \
					 libabc_utils.la


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
	libabc_logging_service.la \
	libabc_terminal_controller.la \
	libabc_utils.la

libabc_io_service_la_LIBADD = \
	libabc_logging_service.la \
	libabc_utils.la

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
libabc_config_service_la_SOURCES       = libs/src/abc_config_service/abc_config_service.c
libabc_utils_la_SOURCES                = libs/src/abc_utils/abc_utils.c


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
libabc_config_service_la_SOURCES       += libs/inc/abc_config_service/abc_config_service.h
libabc_utils_la_SOURCES                += libs/inc/abc_utils/abc_utils.h


#
# Programs
#
bin_PROGRAMS = aubrca

aubrca_LDADD = \
	libabc_brightness_service.la \
	libabc_backlight_controller.la \
	libabc_config_service.la \
	libabc_logging_service.la

aubrca_SOURCES = programs/src/main/main.c


#
# Test libraries
#
AM_CXXFLAGS = -std=c++11 -Wall -Wextra

ABC_TEST_FLAGS = \
	-DABC_LOGGING_ON=1 \
	-DABC_LOGGING_DEFAULT_FILENAME=\"log.log\" \
	-DDEBUG=1 \
	-I$(top_srcdir)/source/libs/inc \
	-I$(top_srcdir)/source/libs/inc_test \
	-I$(top_srcdir)/source/libs/tests/test_lib/inc \
	-DABC_CONFIG_FILENAME=\"aubrca.conf\" \
	-DABC_CONFIG_DEFAULTS_FILENAME=\"defaults.conf\" \
	-DABC_PICTURE_DIR=\"\"

check_LTLIBRARIES = \
	libabc_test.la \
	libabc_logging_service_active.la

#
# CPP testing libraries
#
libabc_test_la_SOURCES  = \
	libs/tests/test_lib/src/testlib_io.cpp \
   	libs/tests/test_lib/inc/testlib_io.h \
	libs/tests/test_lib/inc/testlib_parsing.h

libabc_test_la_CPPFLAGS = $(ABC_TEST_FLAGS)

libabc_test_la_LIBADD = libabc_logging_service_active.la

#
# Testing logging library
#
libabc_logging_service_active_la_SOURCES = $(libabc_logging_service_la_SOURCES)

libabc_logging_service_active_la_CFLAGS  = $(ABC_TEST_FLAGS)


#
# Test executables
#
ABC_TEST_LDLIBS = \
	libabc_test.la \
	libabc_logging_service_active.la \
	-lgtest \
	-lgtest_main \
	-lpthread

check_PROGRAMS = \
	test_abc_ambient_controller \
	test_abc_backlight_controller \
	test_abc_logging_service \
	test_abc_filter \
	test_abc_io_service \
	test_abc_utils \
	test_abc_config_service \
	test_abc_power_controller \
	test_abc_power_controller_upower \
	test_abc_terminal_controller \
	test_abc_brightness_service \
	test_abc_brightness_service_fake_abc_time_service

test_abc_ambient_controller_LDADD                       = $(ABC_TEST_LDLIBS)
test_abc_backlight_controller_LDADD                     = $(ABC_TEST_LDLIBS)
test_abc_logging_service_LDADD                          = libabc_test.la -lgtest -lgtest_main -lpthread
test_abc_brightness_service_LDADD                       = $(ABC_TEST_LDLIBS)
test_abc_brightness_service_fake_abc_time_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_filter_LDADD                                   = $(ABC_TEST_LDLIBS)
test_abc_io_service_LDADD                               = libabc_utils.la $(ABC_TEST_LDLIBS) # No need to fake the abc_utils module.
test_abc_utils_LDADD                                    = $(ABC_TEST_LDLIBS)
test_abc_config_service_LDADD                           = libabc_utils.la $(ABC_TEST_LDLIBS) # No need to fake the abc_utils module.
test_abc_power_controller_LDADD                         = $(ABC_TEST_LDLIBS)
test_abc_power_controller_upower_LDADD                  = $(ABC_TEST_LDLIBS)
test_abc_terminal_controller_LDADD                      = $(ABC_TEST_LDLIBS)

test_abc_ambient_controller_CPPFLAGS                       = $(ABC_TEST_FLAGS)
test_abc_backlight_controller_CPPFLAGS                     = $(ABC_TEST_FLAGS)
test_abc_logging_service_CPPFLAGS                          = $(ABC_TEST_FLAGS)
test_abc_brightness_service_CPPFLAGS                       = $(ABC_TEST_FLAGS)
test_abc_brightness_service_fake_abc_time_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_filter_CPPFLAGS                                   = $(ABC_TEST_FLAGS)
test_abc_io_service_CPPFLAGS                               = $(ABC_TEST_FLAGS)
test_abc_utils_CPPFLAGS                                    = $(ABC_TEST_FLAGS)
test_abc_config_service_CPPFLAGS                           = $(ABC_TEST_FLAGS)
test_abc_power_controller_CPPFLAGS                         = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=0
test_abc_power_controller_upower_CPPFLAGS                  = $(ABC_TEST_FLAGS) -DABC_HAS_UPOWER=1
test_abc_terminal_controller_CPPFLAGS                      = $(ABC_TEST_FLAGS)

test_abc_ambient_controller_CFLAGS                       = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_backlight_controller_CFLAGS                     = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_logging_service_CFLAGS                          = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_brightness_service_CFLAGS                       = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_brightness_service_fake_abc_time_service_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_filter_CFLAGS                                   = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_io_service_CFLAGS                               = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_utils_CFLAGS                                    = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_config_service_CFLAGS                           = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_power_controller_CFLAGS                         = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=0
test_abc_power_controller_upower_CFLAGS                  = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS) -DABC_HAS_UPOWER=1
test_abc_terminal_controller_CFLAGS                      = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)


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

test_abc_config_service_SOURCES = \
	$(libabc_config_service_la_SOURCES) \
	libs/tests/abc_config_service/tests_abc_config_service.cpp \
	libs/inc_test/abc_config_service/fake_abc_terminal_controller.h \
	libs/src_test/abc_config_service/fake_abc_terminal_controller.c

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


TESTS = \
	test_abc_ambient_controller \
	test_abc_backlight_controller \
	test_abc_logging_service \
	test_abc_filter \
	test_abc_io_service \
	test_abc_utils \
	test_abc_config_service \
	test_abc_power_controller_upower \
	test_abc_power_controller \
	test_abc_terminal_controller \
	test_abc_brightness_service \
	test_abc_brightness_service_fake_abc_time_service


#
# Config files
#

# The name "defaultconfigfiles" followed by "dir" allows to extend the
# data-path where the files are installed. In this case we want to install them
# under the "aubrca" directory in "$datadir" rather than in the "$datadir"
# directly.
# The DATA primary enumerates the files we are going to install. The path is in
# the source tree, relative to this Makefile.am.

# The default configuration (not to be changed).
defaultconfigfilesdir = $(datadir)/aubrca
defaultconfigfiles_DATA = data/config/aubrca/defaults.conf

# To create the host configuration, simply replicate the defaults.conf.
data/config/aubrca.conf: data/config/aubrca/defaults.conf
	mkdir -p data/config
	cp -p $< $@

# Let "make clean" remove it.
CLEANFILES = data/config/aubrca.conf

# The host configuration (should be used by the host to configure the program).
sysconf_DATA = data/config/aubrca.conf


#
# Prepare for systemd.
#
systemdunitsdir = $(libdir)/systemd/system
systemdunits_DATA = data/systemd/autobrightnesscam.service


#
# Congregate the data files
#
EXTRA_DIST = data/config/aubrca/defaults.conf \
			 data/systemd/autobrightnesscam.service.in



#
# Systemd banner
#

if ABC_PRINTS_SYSTEMD_BANNER

echo_systemd_banner = \
	@echo "" \
	echo ""; \
	echo "============================================================="; \
	echo "                        README"; \
	echo "============================================================="; \
	echo "To enable automatic startup via systemd, run the following:"; \
	echo ""; \
	echo "On systems with SELinux on, enabling a service not in a default"; \
	echo "location makes enforcing unhappy. So we need to do a heavy systemd"; \
	echo "reload."; \
	echo ""; \
	echo ">>> sudo systemctl daemon-reexec"; \
	echo ">>> sudo systemctl enable $(systemdunitsdir)/autobrightnesscam.service"; \
	echo ">>> sudo systemctl start autobrightnesscam.service"; \
	echo ""; \
	echo ""; \
	echo "Before uninstalling run:"; \
	echo ""; \
	echo ">>> sudo systemctl stop autobrightnesscam.service"; \
	echo ">>> sudo systemctl disable autobrightnesscam.service"; \
	echo ""; \
	echo "============================================================="; \
	echo "                        README"; \
	echo "=============================================================";

else

echo_systemd_banner = @echo ""

endif # if ABC_PRINTS_SYSTEMD_BANNER


#
# Cleaning rules.
#
clean-local: clean-local-check

.PHONY: \
	clean-local-check \
	install-data-local \
	uninstall-local \
	create-systemd-service \
	remove-systemd-service

clean-local-check:
	-rm -f ./*abc*.log ./*abc*.test

#
# Post data installation rule (use the 'local' suffix instead of hook for
# pre-install).
#
install-data-hook:
	-mkdir -p $(localstatedir)/aubrca
	-$(echo_systemd_banner)

UNINSTALL_SYSTEMD_SERVICE_CMDS = \
	systemctl stop autobrightnesscam.service; \
	systemctl disable autobrightnesscam.service;

#
# Post uninstall rule.
#
uninstall-local:
	-rm -rf $(localstatedir)/aubrca
	-rm -rf $(datadir)/aubrca
