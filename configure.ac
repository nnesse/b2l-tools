AC_PREREQ(2.59)
AC_INIT(glplatform, 0.2)

AC_CHECK_LIB([X11],[XOpenDisplay],,AC_MSG_ERROR([Could not find libX11]))
AC_CHECK_LIB([GL],[glXGetProcAddress],,AC_MSG_ERROR([Could not find libGL]))

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([foreign])

LT_INIT()

AC_PROG_CC

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
