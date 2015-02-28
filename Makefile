all: example

gl_4_2.c gl_4_2.h:
	glbindify -a gl -v 4.2

glx_1_4.c glx_1_4.h:
	glbindify -a glx -v 1.4 -e ARB_create_context -e ARB_create_context_profile

example: gl_4_2.c glx_1_4.c glwin.c glwin.h
	gcc glwin.c gl_4_2.c glx_1_4.c example.c -lGL -lX11 -o example

clean:
	@-rm -f example gl_4_2.c gl_4_2.h glx_1_4.c glx_1_4.h
