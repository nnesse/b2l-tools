all: example

glb_gl.c glb_gl.h:
	glbindify -a gl

glb_glx.c glb_glx.h:
	glbindify -a glx -e ARB_create_context -e ARB_create_context_profile

example: glb_gl.c glb_glx.c glb_gl.h glb_glx.h glwin.c glwin.h
	gcc glwin.c glb_gl.c glb_glx.c example.c -lGL -lX11 -o example

clean:
	@-rm -f example glb_*.?
