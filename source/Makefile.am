
#
# Warning flags
#
C_WARNING_FLAGS = -Wall \
		  -Wpedantic \
		  -Wextra \
		  -Wno-unknown-warning \
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
		  -Wconversion -Wno-sign-conversion \
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
# Global build flags
#
AM_CFLAGS   = -std=gnu99 $(C_WARNING_FLAGS) -I$(top_srcdir)/source/libs/inc
AM_CXXFLAGS = -std=c++11 -Wall -Wextra -I$(top_srcdir)/source/libs/inc


#
# Libraries
#
noinst_LTLIBRARIES = libabc_ambient_controller.la \
		     libabc_backlight_controller.la \
		     libabc_brightness_service.la \
		     libabc_filter.la \
		     libabc_io_service.la \
		     libabc_logging_service.la \
		     libabc_power_controller.la \
		     libabc_terminal_controller.la \
		     libabc_time_service.la

libabc_filter_la_LIBADD = libabc_logging_service.la
libabc_io_service_la_LIBADD = libabc_logging_service.la
libabc_terminal_controller_la_LIBADD = libabc_logging_service.la
libabc_time_service_la_LIBADD = libabc_logging_service.la
libabc_power_controller_la_LIBADD = libabc_terminal_controller.la \
				    libabc_logging_service.la
libabc_ambient_controller_la_LIBADD = libabc_terminal_controller.la \
						 libabc_logging_service.la
libabc_backlight_controller_la_LIBADD = libabc_logging_service.la \
						   libabc_io_service.la \
						   libabc_time_service.la
libabc_brightness_service_la_LIBADD = libabc_power_controller.la \
				      libabc_ambient_controller.la \
				      libabc_backlight_controller.la \
				      libabc_time_service.la \
				      libabc_logging_service.la \
				      libabc_filter.la

libabc_ambient_controller_la_SOURCES   = $(top_srcdir)/source/libs/src/abc_ambient_controller/abc_ambient_controller.c
libabc_backlight_controller_la_SOURCES = $(top_srcdir)/source/libs/src/abc_backlight_controller/abc_backlight_controller.c
libabc_brightness_service_la_SOURCES              = $(top_srcdir)/source/libs/src/abc_brightness_service/abc_brightness_service.c
libabc_filter_la_SOURCES                          = $(top_srcdir)/source/libs/src/abc_filter/abc_filter.c
libabc_io_service_la_SOURCES                      = $(top_srcdir)/source/libs/src/abc_io_service/abc_io_service.c
libabc_logging_service_la_SOURCES                 = $(top_srcdir)/source/libs/src/abc_logging_service/abc_logging_service.c
libabc_power_controller_la_SOURCES                = $(top_srcdir)/source/libs/src/abc_power_controller/abc_power_controller.c
libabc_terminal_controller_la_SOURCES             = $(top_srcdir)/source/libs/src/abc_terminal_controller/abc_terminal_controller.c
libabc_time_service_la_SOURCES                    = $(top_srcdir)/source/libs/src/abc_time_service/abc_time_service.c

libabc_ambient_controller_la_SOURCES   += $(top_srcdir)/source/libs/inc/abc_ambient_controller/abc_ambient_controller.h
libabc_backlight_controller_la_SOURCES += $(top_srcdir)/source/libs/inc/abc_backlight_controller/abc_backlight_controller.h
libabc_brightness_service_la_SOURCES              += $(top_srcdir)/source/libs/inc/abc_brightness_service/abc_brightness_service.h
libabc_filter_la_SOURCES                          += $(top_srcdir)/source/libs/inc/abc_filter/abc_filter.h
libabc_io_service_la_SOURCES                      += $(top_srcdir)/source/libs/inc/abc_io_service/abc_io_service.h
libabc_logging_service_la_SOURCES                 += $(top_srcdir)/source/libs/inc/abc_logging_service/abc_logging_service.h
libabc_power_controller_la_SOURCES                += $(top_srcdir)/source/libs/inc/abc_power_controller/abc_power_controller.h
libabc_terminal_controller_la_SOURCES             += $(top_srcdir)/source/libs/inc/abc_terminal_controller/abc_terminal_controller.h
libabc_time_service_la_SOURCES                    += $(top_srcdir)/source/libs/inc/abc_time_service/abc_time_service.h


#
# Programs
#
bin_PROGRAMS = aubrca

aubrca_LDADD   = libabc_brightness_service.la
aubrca_SOURCES = $(top_srcdir)/source/programs/src/main/main.c


#
# Test libraries
#
ABC_TEST_FLAGS = -DABC_LOGGING_ON=1 -I$(top_srcdir)/source/libs/inc -I$(top_srcdir)/source/libs/inc_test -I$(top_srcdir)/source/libs/tests/test_lib/inc

check_LTLIBRARIES = libabc_test.la libabc_logging_service_active.la

libabc_test_la_SOURCES  = $(top_srcdir)/source/libs/tests/test_lib/src/testlib_io.cpp
libabc_test_la_SOURCES += $(top_srcdir)/source/libs/tests/test_lib/inc/testlib_io.h
libabc_test_la_SOURCES += $(top_srcdir)/source/libs/tests/test_lib/inc/testlib_parsing.h
libabc_test_la_CPPFLAGS = $(ABC_TEST_FLAGS)
libabc_test_la_LIBADD   = libabc_logging_service_active.la

libabc_logging_service_active_la_SOURCES = $(libabc_logging_service_la_SOURCES)
libabc_logging_service_active_la_CFLAGS  = $(ABC_TEST_FLAGS)


#
# Test executables
#
ABC_TEST_LDLIBS = libabc_test.la libabc_logging_service_active.la -lgtest -lgtest_main -lpthread

check_PROGRAMS = test_abc_ambient_controller \
		 test_abc_backlight_controller \
		 test_abc_logging_service \
		 test_abc_filter \
		 test_abc_io_service \
		 test_abc_power_controller \
		 test_abc_terminal_controller \
		 test_abc_brightness_service \
		 test_abc_brightness_service_fake_abc_time_service

test_abc_ambient_controller_LDADD = $(ABC_TEST_LDLIBS)
test_abc_backlight_controller_LDADD = $(ABC_TEST_LDLIBS)
test_abc_logging_service_LDADD = libabc_test.la -lgtest -lgtest_main -lpthread
test_abc_brightness_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_brightness_service_fake_abc_time_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_filter_LDADD = $(ABC_TEST_LDLIBS)
test_abc_io_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_power_controller_LDADD = $(ABC_TEST_LDLIBS)
test_abc_terminal_controller_LDADD = $(ABC_TEST_LDLIBS)

test_abc_ambient_controller_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_backlight_controller_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_logging_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_brightness_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_brightness_service_fake_abc_time_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_filter_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_io_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_power_controller_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_terminal_controller_CPPFLAGS = $(ABC_TEST_FLAGS)

test_abc_ambient_controller_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_backlight_controller_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_logging_service_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_brightness_service_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_brightness_service_fake_abc_time_service_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_filter_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_io_service_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_power_controller_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)
test_abc_terminal_controller_CFLAGS = $(ABC_TEST_FLAGS) $(C_WARNING_FLAGS)


test_abc_ambient_controller_SOURCES = $(libabc_ambient_controller_la_SOURCES) \
						 $(top_srcdir)/source/libs/src_test/abc_ambient_controller/fake_abc_terminal_controller.c \
						 $(top_srcdir)/source/libs/tests/abc_ambient_controller/tests_abc_ambient_controller.cpp
test_abc_ambient_controller_SOURCES += $(top_srcdir)/source/libs/inc_test/abc_ambient_controller/fake_abc_terminal_controller.h


test_abc_backlight_controller_SOURCES = $(libabc_backlight_controller_la_SOURCES) \
						   $(top_srcdir)/source/libs/tests/abc_backlight_controller/tests_abc_backlight_controller.cpp \
						   $(top_srcdir)/source/libs/src_test/abc_backlight_controller/fake_abc_io_service.c \
						   $(top_srcdir)/source/libs/src_test/abc_backlight_controller/fake_abc_time_service.c
test_abc_backlight_controller_SOURCES += $(top_srcdir)/source/libs/inc_test/abc_backlight_controller/fake_abc_io_service.h


test_abc_logging_service_SOURCES = $(libabc_logging_service_la_SOURCES) \
				   $(top_srcdir)/source/libs/tests/abc_logging_service/tests_abc_logging_service.cpp

test_abc_brightness_service_SOURCES = $(libabc_brightness_service_la_SOURCES) \
				      $(top_srcdir)/source/libs/tests/abc_brightness_service/tests_abc_brightness_service.cpp \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_ambient_controller.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_backlight_controller.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_filter.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_power_controller.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_time_service.c
test_abc_brightness_service_SOURCES += $(top_srcdir)/source/libs/inc_test/abc_brightness_service/fake_abc_ambient_controller.h \
				       $(top_srcdir)/source/libs/inc_test/abc_brightness_service/fake_abc_backlight_controller.h \
				       $(top_srcdir)/source/libs/inc_test/abc_brightness_service/fake_abc_filter.h \
				       $(top_srcdir)/source/libs/inc_test/abc_brightness_service/fake_abc_power_controller.h \
				       $(top_srcdir)/source/libs/inc_test/abc_brightness_service/fake_abc_time_service.h

test_abc_brightness_service_fake_abc_time_service_SOURCES = $(top_srcdir)/source/libs/tests/abc_brightness_service/tests_fake_abc_time_service.cpp \
							    $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_time_service.c


test_abc_filter_SOURCES = $(libabc_filter_la_SOURCES) \
			  $(top_srcdir)/source/libs/tests/abc_filter/tests_abc_filter.cpp

test_abc_io_service_SOURCES = $(libabc_io_service_la_SOURCES) \
			      $(top_srcdir)/source/libs/tests/abc_io_service/tests_abc_io_service.cpp


test_abc_power_controller_SOURCES = $(libabc_power_controller_la_SOURCES) \
				    $(top_srcdir)/source/libs/tests/abc_power_controller/tests_abc_power_controller.cpp \
				    $(top_srcdir)/source/libs/src_test/abc_power_controller/fake_abc_terminal_controller.c
test_abc_power_controller_SOURCES += $(top_srcdir)/source/libs/inc_test/abc_power_controller/fake_abc_terminal_controller.h

test_abc_terminal_controller_SOURCES = $(libabc_terminal_controller_la_SOURCES) \
				       $(top_srcdir)/source/libs/tests/abc_terminal_controller/tests_abc_terminal_controller.cpp


TESTS = test_abc_ambient_controller \
	test_abc_backlight_controller \
	test_abc_logging_service \
	test_abc_filter \
	test_abc_io_service \
	test_abc_power_controller \
	test_abc_terminal_controller \
	test_abc_brightness_service \
	test_abc_brightness_service_fake_abc_time_service

clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -f ./*abc*.log ./*abc*.test /tmp/brightness.jpg
