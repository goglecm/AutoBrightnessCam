#
# Initialise autoconf
#
AC_INIT([AutoBrightnessCam], [1.0], [yv3r3nd5yi1k@mail.ru])


#
# Configure arguments
#
AC_ARG_ENABLE([depscheck],
              AS_HELP_STRING([--disable-depscheck],
                             [Do not complain about missing dependencies]))
AC_ARG_ENABLE([debug],
              AS_HELP_STRING([--enable-debug],
                             [Turn on assertions and debugging symbols]))
AC_ARG_ENABLE([skipsystemctlcalls],
              AS_HELP_STRING([--enable-skipsystemctlcalls],
                             [Do not make calls to systemctl during install and
                              uninstall]))

AC_ARG_WITH([upower],
            AS_HELP_STRING([--without-upower],
                           [Detect the battery charging status manually]))


#
# Initialise automake
#
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_MACRO_DIR([m4])


#
# Some more build dependencies
#
AM_PROG_AR
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CXX
AM_PROG_CC_C_O


#
# Initialise libtool
#
LT_INIT


#
# Mandatory runtime dependencies
#
AC_CHECK_PROG(exists_fswebcam, fswebcam, yes, no)
AC_CHECK_PROG(exists_convert,  convert,  yes, no)


#
# Optional runtime dependencies
#
AC_CHECK_PROG(exists_sed,     sed,       yes, no)
AC_CHECK_PROG(exists_grep,    grep,      yes, no)
AC_CHECK_PROG(exists_upower,  upower,    yes, no)
AC_CHECK_PROG(exists_systemd, systemctl, yes, no)


#
# Check the runtime dependencies
#
AS_IF([ test "x$exists_fswebcam" == "xno" && test "x$enable_depscheck" != "xno" ],
      [ AC_MSG_ERROR([Please install fswebcam.])],
      [ test "x$exists_convert"  == "xno" && test "x$enable_depscheck" != "xno" ],
      [ AC_MSG_ERROR([Please install ImageMagick which provides convert.])])


#
# Debug
#
AM_CONDITIONAL([ABC_USES_DEBUG], test "x$enable_debug" == "xyes")

#
# Upower
#
AS_IF([ test "x$exists_upower" == "xyes" &&
        test "x$exists_sed"    == "xyes" &&
        test "x$exists_grep"   == "xyes" ],
      [ upower_has_all_deps="yes" ],
      [ upower_has_all_deps="no"  ])

AS_IF([ test "x$with_upower" == "xyes" ],
      [ AS_IF([ test "x$upower_has_all_deps" == "xyes" ],
              [ use_upower="yes"                       ],
              [ test "x$enable_depscheck"    != "xno"  ],
              [ AC_MSG_ERROR([Trying to use upower when it is not installed])],
              [ use_upower="no"                        ])],
      [ test "x$with_upower" == "xno"     ],
      [ use_upower="no"                   ],
      [ use_upower="$upower_has_all_deps"])

AS_IF([ test "x$use_upower" == "xyes" ],
      [ AC_CHECK_HEADER([sys/stat.h], [], [AC_MSG_ERROR([Missing sys/stat.h])])])

AM_CONDITIONAL([ABC_USES_UPOWER], test "x$use_upower" == "xyes")


#
# Systemd
#
AS_IF([ test "x$enable_skipsystemctlcalls" == "xno" ],
      AS_IF([ test "x$exists_systemd" == "xyes"     ],
            [ allow_systemctl_calls="yes"           ],
            [ test "x$enable_depscheck" != "xno"    ],
            [ AC_MSG_ERROR([Trying to call systemctl when it is not installed.])],
            [ allow_systemctl_calls="no"            ] ),
      [ test "x$enable_skipsystemctlcalls" == "xyes" ],
      [ allow_systemctl_calls="no"                   ],
      [ allow_systemctl_calls="$exists_systemd"      ])

AM_CONDITIONAL([ABC_USES_SYSTEMD], test "x$allow_systemctl_calls" == "xyes")

#
# Config files
#
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 source/Makefile
                 source/data/systemd/autobrightnesscam.service])

AC_OUTPUT

