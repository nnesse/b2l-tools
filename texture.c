#include "texture.h"

#include "lua.h"

#include "glplatform-glcore.h"

static int texture_gc(lua_State *L)
{
	struct texture *t = lua_touserdata(L, -1);
	glDeleteTextures(1, &t->texid);
	return 0;
}

void ltexture_create(lua_State *L, GdkPixbuf *pbuf)
{
	GLuint texid;
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);

	int width = gdk_pixbuf_get_width(pbuf);
	int height = gdk_pixbuf_get_height(pbuf);
	int n_chan = gdk_pixbuf_get_n_channels(pbuf);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, gdk_pixbuf_get_rowstride(pbuf)/ n_chan);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D,
		0, /* level */
		n_chan > 3 ? GL_RGBA : GL_RGB,
		width,
		height,
		0, /* border */
		n_chan > 3 ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		gdk_pixbuf_get_pixels(pbuf));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	struct texture *t = lua_newuserdata(L, sizeof(struct texture));
	t->texid = texid;

	lua_newtable(L);
	lua_pushcfunction(L, texture_gc);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
}
