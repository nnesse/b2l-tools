all: example

glb-glx.c glb-glx.h:
	glbindify -a glx

CFLAGS := $(CFLAGS) `pkg-config glb-glcore --cflags`
LDFLAGS := $(LDFLAGS) `pkg-config glb-glcore --libs`

example: glb-glx.c glb-glx.h glwin.c glwin.h
	gcc glwin.c glb-glx.c $(CFLAGS) example.c $(LDFLAGS) -lGL -lX11 -o example

clean:
	@-rm -f example glb-*.?
