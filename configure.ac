AC_PREREQ(2.59)
AC_INIT(glplatform, 0.3)

AC_ARG_ENABLE([text], AS_HELP_STRING([--enable-text], [Enables text rendering API]))

if test x$enable_text = x; then
	enable_text="yes"
fi
echo asfasf $enable_text

if test $enable_text = yes; then
	PKG_CHECK_MODULES(FREETYPE2,freetype2 >= 2.53, [ enable_text="yes" ], [ enable_text="no" ])
fi

AC_CHECK_LIB([X11],[XOpenDisplay],,AC_MSG_ERROR([Could not find libX11]))
AC_CHECK_LIB([GL],[glXGetProcAddress],,AC_MSG_ERROR([Could not find libGL]))

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([foreign subdir-objects])

AM_CONDITIONAL([WITH_TEXT], [ test $enable_text = yes ])

LT_INIT()

AC_PROG_CC

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
