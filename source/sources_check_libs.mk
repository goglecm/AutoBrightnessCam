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

