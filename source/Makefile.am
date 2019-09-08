C_WARNING_FLAGS = -Wall \
		  -Wpedantic \
		  -Wextra \
		  -Werror \
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

AM_CFLAGS = -std=gnu99 $(C_WARNING_FLAGS) -I$(top_srcdir)/source/libs/inc

AM_CXXFLAGS = -std=c++11 -Wall -Wextra -I$(top_srcdir)/source/libs/inc

#
# Libraries
#
noinst_LTLIBRARIES = libabc_ambient_brightness_controller.la \
		     libabc_backlight_brightness_controller.la \
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

libabc_ambient_brightness_controller_la_LIBADD = libabc_terminal_controller.la \
						 libabc_logging_service.la

libabc_backlight_brightness_controller_la_LIBADD = libabc_logging_service.la \
						   libabc_io_service.la \
						   libabc_time_service.la

libabc_brightness_service_la_LIBADD = libabc_power_controller.la \
				      libabc_ambient_brightness_controller.la \
				      libabc_backlight_brightness_controller.la \
				      libabc_time_service.la \
				      libabc_logging_service.la \
				      libabc_filter.la

libabc_ambient_brightness_controller_la_SOURCES   = $(top_srcdir)/source/libs/src/abc_ambient_brightness_controller/abc_ambient_brightness_controller.c
libabc_backlight_brightness_controller_la_SOURCES = $(top_srcdir)/source/libs/src/abc_backlight_brightness_controller/abc_backlight_brightness_controller.c
libabc_brightness_service_la_SOURCES              = $(top_srcdir)/source/libs/src/abc_brightness_service/abc_brightness_service.c
libabc_filter_la_SOURCES                          = $(top_srcdir)/source/libs/src/abc_filter/abc_filter.c
libabc_io_service_la_SOURCES                      = $(top_srcdir)/source/libs/src/abc_io_service/abc_io_service.c
libabc_logging_service_la_SOURCES                 = $(top_srcdir)/source/libs/src/abc_logging_service/abc_logging_service.c
libabc_power_controller_la_SOURCES                = $(top_srcdir)/source/libs/src/abc_power_controller/abc_power_controller.c
libabc_terminal_controller_la_SOURCES             = $(top_srcdir)/source/libs/src/abc_terminal_controller/abc_terminal_controller.c
libabc_time_service_la_SOURCES                    = $(top_srcdir)/source/libs/src/abc_time_service/abc_time_service.c


#
# Programs
#
bin_PROGRAMS = aubrca

aubrca_LDADD   = libabc_brightness_service.la
aubrca_SOURCES = $(top_srcdir)/source/programs/src/main/main.c


#
# Test libraries
#
ABC_TEST_FLAGS = -I$(top_srcdir)/source/libs/inc_test -I$(top_srcdir)/source/libs/tests/test_lib/inc

check_LTLIBRARIES = libabc_test.la

libabc_test_la_SOURCES = $(top_srcdir)/source/libs/tests/test_lib/src/testlib_io.cpp
libabc_test_la_CPPFLAGS = $(ABC_TEST_FLAGS)
libabc_test_la_LIBADD = libabc_logging_service.la


#
# Test executables
#
ABC_TEST_LDLIBS = libabc_test.la libabc_logging_service.la -lgtest -lgtest_main -lpthread

check_PROGRAMS = test_abc_ambient_brightness_controller \
		 test_abc_backlight_brightness_controller \
		 test_abc_logging_service \
		 test_abc_filter \
		 test_abc_io_service \
		 test_abc_power_controller \
		 test_abc_terminal_controller \
		 test_abc_brightness_service \
		 test_abc_brightness_service_fake_abc_time_service

test_abc_ambient_brightness_controller_LDADD = $(ABC_TEST_LDLIBS)
test_abc_backlight_brightness_controller_LDADD = $(ABC_TEST_LDLIBS)
test_abc_logging_service_LDADD = libabc_test.la -lgtest -lgtest_main -lpthread
test_abc_brightness_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_brightness_service_fake_abc_time_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_filter_LDADD = $(ABC_TEST_LDLIBS)
test_abc_io_service_LDADD = $(ABC_TEST_LDLIBS)
test_abc_power_controller_LDADD = $(ABC_TEST_LDLIBS)
test_abc_terminal_controller_LDADD = $(ABC_TEST_LDLIBS)


test_abc_ambient_brightness_controller_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_backlight_brightness_controller_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_logging_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_brightness_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_brightness_service_fake_abc_time_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_filter_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_io_service_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_power_controller_CPPFLAGS = $(ABC_TEST_FLAGS)
test_abc_terminal_controller_CPPFLAGS = $(ABC_TEST_FLAGS)


test_abc_ambient_brightness_controller_SOURCES = $(libabc_ambient_brightness_controller_la_SOURCES) \
						 $(top_srcdir)/source/libs/tests/abc_ambient_brightness_controller/tests_abc_ambient_brightness_controller.cpp \
						 $(top_srcdir)/source/libs/src_test/abc_ambient_brightness_controller/fake_abc_terminal_controller.c

test_abc_backlight_brightness_controller_SOURCES = $(libabc_backlight_brightness_controller_la_SOURCES) \
						   $(top_srcdir)/source/libs/tests/abc_backlight_brightness_controller/tests_abc_backlight_brightness_controller.cpp \
						   $(top_srcdir)/source/libs/src_test/abc_backlight_brightness_controller/fake_abc_io_service.c \
						   $(top_srcdir)/source/libs/src_test/abc_backlight_brightness_controller/fake_abc_time_service.c

test_abc_logging_service_SOURCES = $(libabc_logging_service_la_SOURCES) \
				   $(top_srcdir)/source/libs/tests/abc_logging_service/tests_abc_logging_service.cpp

test_abc_brightness_service_SOURCES = $(libabc_brightness_service_la_SOURCES) \
				      $(top_srcdir)/source/libs/tests/abc_brightness_service/tests_abc_brightness_service.cpp \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_ambient_brightness_controller.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_backlight_brightness_controller.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_filter.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_power_controller.c \
				      $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_time_service.c

test_abc_brightness_service_fake_abc_time_service_SOURCES = $(top_srcdir)/source/libs/tests/abc_brightness_service/tests_fake_abc_time_service.cpp \
							    $(top_srcdir)/source/libs/src_test/abc_brightness_service/fake_abc_time_service.c

test_abc_filter_SOURCES = $(libabc_filter_la_SOURCES) \
			  $(top_srcdir)/source/libs/tests/abc_filter/tests_abc_filter.cpp

test_abc_io_service_SOURCES = $(libabc_io_service_la_SOURCES) \
			      $(top_srcdir)/source/libs/tests/abc_io_service/tests_abc_io_service.cpp


test_abc_power_controller_SOURCES = $(libabc_power_controller_la_SOURCES) \
				    $(top_srcdir)/source/libs/tests/abc_power_controller/tests_abc_power_controller.cpp \
				    $(top_srcdir)/source/libs/src_test/abc_power_controller/fake_abc_terminal_controller.c

test_abc_terminal_controller_SOURCES = $(libabc_terminal_controller_la_SOURCES) \
				       $(top_srcdir)/source/libs/tests/abc_terminal_controller/tests_abc_terminal_controller.cpp


TESTS = test_abc_ambient_brightness_controller \
	test_abc_backlight_brightness_controller \
	test_abc_logging_service \
	test_abc_filter \
	test_abc_io_service \
	test_abc_power_controller \
	test_abc_terminal_controller \
	test_abc_brightness_service \
	test_abc_brightness_service_fake_abc_time_service
