#
# Initialise autoconf
#
AC_INIT([AutoBrightnessCam], [2.0], [yv3r3nd5yi1k@mail.ru])


#
# Configure arguments
#
AC_ARG_ENABLE([depscheck],
              AS_HELP_STRING([--disable-depscheck],
                             [Do not complain about missing dependencies]))
AC_ARG_ENABLE([systemdbanner],
              AS_HELP_STRING([--disable-systemdbanner],
                             [Do not display instructions on how to install a
                              systemd service]))
AC_ARG_ENABLE([debug],
              AS_HELP_STRING([--enable-debug],
                             [Turn on assertions and debugging symbols]))

AC_ARG_WITH([upower],
            AS_HELP_STRING([--without-upower],
                           [Detect the battery charging status manually]))

AC_ARG_WITH([gui],
            AS_HELP_STRING([--with-gui],
                           [Build the user interface app as well]))

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
AC_PROG_MKDIR_P
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

#
# Mandatory build dependencies
#





    #############################################################
    #                                                           #
    #                           NOTE:                           #
    #                                                           #
    # Spaces are required around "==" and other equality signs. #
    #                                                           #
    # Spaces should not be put around assignments "=".          #
    #                                                           #
    #############################################################





# This generates LIBCONFIG_CFLAGS and _LIBS.
PKG_CHECK_MODULES([LIBCONFIG], [libconfig >= 1.4],
                  [ libconfig_exists="yes" ],
                  [ libconfig_exists="no" ])


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
# GUI app
#
AS_IF([ test "x$with_gui" == "xyes" ],
      [ PKG_CHECK_MODULES([GTK4], [gtk4],
                          [ gtk4_exists="yes" ],
                          [ gtk4_exists="no"  ]) ], [])

AS_IF([ test "x$with_gui" == "xyes" ],
      [ AS_IF([ test "x$gtk4_exists" == "xyes" ],
              [ AC_MSG_NOTICE([Building the GUI as gtk4 exists]) ],
              [ AC_MSG_ERROR([gtk4-devel is not available ]) ]) ],
      [ AC_MSG_NOTICE([Not building the GUI]) ])

AM_CONDITIONAL([ABC_USE_GUI], [ test "x$with_gui" == "xyes" ])


#
# Systemd banner
#
AM_CONDITIONAL([ABC_PRINTS_SYSTEMD_BANNER], test "x$enable_systemdbanner" != "xno")


#
# Parser
#

AS_IF([ test "x$libconfig_exists" == "xyes" ],
      [],
      [ AC_MSG_ERROR([ libconfig 1.4 or newer not found ]) ])


#
# Config files
#
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 source/Makefile
                 source/data/systemd/autobrightnesscam.service])

AC_OUTPUT
