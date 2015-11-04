#ifndef TEXTURE_H
#define TEXTURE_H

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "lua.h"

struct texture {
	unsigned int texid;
};

void ltexture_create(lua_State *L, GdkPixbuf *pbuf);

#endif
