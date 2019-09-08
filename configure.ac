AC_INIT([aubrca], [0.1], [yv3r3nd5yi1k@mail.ru])

AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([subdir-objects])

AM_PROG_AR
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CXX
AC_PROG_GREP

AC_CHECK_PROG(HAS_ABC_FSWEBCAM, fswebcam, 1, 0)
if test ${HAS_ABC_FSWEBCAM} == 0 ; then
    AC_MSG_ERROR([Please install fswebcam from remi repo.])
fi

AC_CHECK_PROG(HAS_ABC_CONVERT, convert, 1, 0)
if test ${HAS_ABC_CONVERT} == 0 ; then
    AC_MSG_WARN([Please install ImageMagick which provides convert and TODO convert this to an error.])
fi

AC_CHECK_PROG(HAS_ABC_SED, sed, 1, 0)
if test ${HAS_ABC_SED} == 0 ; then
    AC_MSG_ERROR([sed is missing please install it.])
fi

AC_CHECK_PROG(HAS_ABC_UPOWER, upower, 1, 0)
if test ${HAS_ABC_UPOWER} == 0 ; then
    AC_MSG_WARN([upower is missing will assume the device is always discharging])
fi


LT_INIT

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile source/Makefile])

AC_OUTPUT

