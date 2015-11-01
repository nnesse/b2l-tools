AM_CFLAGS:=-Wall -Wno-unused-function

AM_CFLAGS+= -DLUA_USE_LINUX \
	-DLUA_COMPAT_ALL \
	-DDATA_DIR=\"$(datadir)/b2l\"

AM_CFLAGS+= -I$(builddir) \
	-I$(builddir)/glsl-parser \
	-I$(srcdir)/glsl-parser \
	-I$(builddir)/glplatform \
	-I$(srcdir)/glplatform \
	-I$(srcdir) \
	-I${srcdir}/lua/src \
	-I${srcdir}/lgi/lgi

AM_CFLAGS+= $(GLIB2_CFLAGS) \
	$(GDKPIXBUF2_CFLAGS) \
	$(GMODULE2_CFLAGS) \
	$(LIBFFI_CFLAGS) \
	$(GOBJECT_INTROSPECTION_CFLAGS) \
	$(GTK3_CFLAGS)

AM_LDFLAGS:= $(GLIB2_LIBS) \
	$(GDKPIXBUF2_LIBS) \
	$(GMODULE2_LIBS) \
	$(LIBFFI_LIBS) \
	$(GOBJECT_INTROSPECTION_LIBS) \
	$(GTK3_LIBS)

LUA_SRC := lua/src/lapi.c \
	lua/src/lcode.c \
	lua/src/lctype.c \
	lua/src/ldebug.c \
	lua/src/ldo.c \
	lua/src/ldump.c \
	lua/src/lfunc.c \
	lua/src/lgc.c \
	lua/src/llex.c \
	lua/src/lmem.c \
	lua/src/lobject.c \
	lua/src/lopcodes.c \
	lua/src/lparser.c \
	lua/src/lstate.c \
	lua/src/lstring.c \
	lua/src/ltable.c \
	lua/src/ltm.c \
	lua/src/lundump.c \
	lua/src/lvm.c \
	lua/src/lzio.c \
	lua/src/lauxlib.c \
	lua/src/lbaselib.c \
	lua/src/lbitlib.c \
	lua/src/lcorolib.c \
	lua/src/ldblib.c \
	lua/src/liolib.c \
	lua/src/lmathlib.c \
	lua/src/loslib.c \
	lua/src/lstrlib.c \
	lua/src/ltablib.c \
	lua/src/loadlib.c \
	lua/src/linit.c

noinst_LIBRARIES = liblua.a liblgi.a
liblua_a_SOURCES = $(LUA_SRC)

LGI_SRC := lgi/lgi/buffer.c \
	lgi/lgi/callable.c \
	lgi/lgi/core.c \
	lgi/lgi/gi.c \
	lgi/lgi/marshal.c \
	lgi/lgi/object.c \
	lgi/lgi/record.c

liblgi_a_SOURCES = $(LGI_SRC)


GLSL_PARSER_SRC := glsl-parser/glsl.parser.c \
	glsl-parser/glsl.lexer.c \
	glsl-parser/glsl_regen.c \
	glsl-parser/glsl_ast.c

GLPLATFORM_SRC := glplatform/glplatform-linux.c \
	glplatform/glplatform-glcore.c \
	glplatform/glplatform-glx.c

BUILT_SOURCES=glsl-parser/glsl.lexer.c \
	      glsl-parser/glsl.parser.c

CLEAN_FILES=$(BUILT_SOURCES) \
	    glsl-parser/glsl.lexer.h \
	    glsl-parser/glsl.parser.h

glsl-parser/glsl.lexer.c: glsl-parser/glsl.lex
	$(FLEX) --header-file=glsl-parser/glsl.lexer.h -o $@ $<

glsl-parser/glsl.parser.c: glsl-parser/glsl.y
	$(BISON) --defines=glsl-parser/glsl.parser.h  $< -o $@

luadir = $(datadir)/b2l/
lgidir = $(datadir)/b2l/lgi
lgi_lgidir = $(datadir)/b2l/lgi/lgi
lgi_lgi_overridedir = $(datadir)/b2l/lgi/lgi/override

lua_DATA := material_editor.lua \
	pprint.lua

lgi_DATA := lgi/lgi.lua

lgi_lgi_DATA := lgi/lgi/class.lua \
	lgi/lgi/core.lua \
	lgi/lgi/ffi.lua \
	lgi/lgi/log.lua \
	lgi/lgi/package.lua \
	lgi/lgi/version.lua \
	lgi/lgi/component.lua \
	lgi/lgi/enum.lua \
	lgi/lgi/init.lua \
	lgi/lgi/namespace.lua \
	lgi/lgi/record.lua

lgi_lgi_override_DATA := lgi/lgi/override/Clutter.lua \
	lgi/lgi/override/GObject-Closure.lua \
	lgi/lgi/override/Gst.lua \
	lgi/lgi/override/GLib-Bytes.lua \
	lgi/lgi/override/GObject-Object.lua \
	lgi/lgi/override/Gtk.lua \
	lgi/lgi/override/GLib-Error.lua \
	lgi/lgi/override/GObject-Type.lua \
	lgi/lgi/override/Pango.lua \
	lgi/lgi/override/GLib-Markup.lua \
	lgi/lgi/override/GObject-Value.lua \
	lgi/lgi/override/PangoCairo.lua \
	lgi/lgi/override/GLib-Timer.lua \
	lgi/lgi/override/Gdk.lua \
	lgi/lgi/override/cairo.lua \
	lgi/lgi/override/GLib-Variant.lua \
	lgi/lgi/override/Gio-DBus.lua \
	lgi/lgi/override/GLib.lua \
	lgi/lgi/override/Gio.lua

bin_PROGRAMS=b2l_material_editor
b2l_material_editor_SOURCES= $(GLSL_PARSER_SRC) \
	$(GLPLATFORM_SRC) \
	b2l_material_editor.c \
	vectormath.c \
	geometry.c \
	mesh.c \
	program.c
b2l_material_editor_LDADD = liblua.a liblgi.a
