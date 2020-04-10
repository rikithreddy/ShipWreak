CC=gcc
CFLAGS=-Wall -I.
CFLAGS+=-lGL -lGLU -lglut

FILES=main.c utils.c opengl_funcs.c

all:
	$(CC) $(FILES) $(CFLAGS) -o shipwreak;

clean:
	rm shipwreak