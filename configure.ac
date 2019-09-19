AC_INIT([aubrca], [0.1], [yv3r3nd5yi1k@mail.ru])

AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([subdir-objects])

AM_PROG_AR
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CXX
AM_PROG_CC_C_O

AC_CHECK_PROG(EXISTS_FSWEBCAM, fswebcam, 1, 0)
if test ${EXISTS_FSWEBCAM} == 0 ; then
    AC_MSG_ERROR([Please install fswebcam.])
fi

AC_CHECK_PROG(EXISTS_CONVERT, convert, 1, 0)
if test ${EXISTS_CONVERT} == 0 ; then
    AC_MSG_ERROR([Please install ImageMagick which provides convert.])
fi

AC_CHECK_PROG(EXISTS_SED, sed, 1, 0)
if test ${EXISTS_SED} == 0 ; then
    AC_MSG_ERROR([Please install sed.])
fi

AC_CHECK_PROG(EXISTS_GREP, grep, 1, 0)
if test ${EXISTS_GREP} == 0 ; then
    AC_MSG_ERROR([Please install grep.])
fi

AC_CHECK_PROG(EXISTS_UPOWER, upower, 1, 0)

AM_CONDITIONAL([ABC_HAS_UPOWER], [test x$EXISTS_UPOWER == x1 &&
                                  test x$EXISTS_SED    == x1 &&
                                  test x$EXISTS_GREP   == x1])

#
# FIXME : check for gtest headers.
#
# AC_CHECK_HEADER([gtest/gtest.h], [], [AC_MSG_WARN([Missing gtest, cannot run tests])])

if test ${EXISTS_UPOWER} == 1 ; then

    AC_CHECK_HEADER([sys/stat.h],
                    [],
                    [AC_MSG_ERROR([Missing sys/stat.h, cannot check files])])

fi

LT_INIT

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 source/Makefile
                 source/data/systemd/autobrightnesscam.service])

AC_OUTPUT

