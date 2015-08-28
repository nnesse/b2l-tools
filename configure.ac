AC_PREREQ(2.59)
AC_INIT(gltext, 0.1)

LT_INIT()

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([foreign])

PKG_CHECK_MODULES(FREETYPE2,freetype2 >= 2.53)
AC_CHECK_LIB([glplatform], [glwin_init], LIBS="-lglplatform $LIBS", AC_MSG_ERROR([Unable to find glplatform]))
AC_PROG_CC

AC_CONFIG_FILES(Makefile examples/Makefile)
AC_OUTPUT
