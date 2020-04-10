CC=gcc
CFLAGS=-Wall -I.
CFLAGS+=-lGL -lGLU -lglut
FILES=main.c
CFLAGS2 = -ansi -pedantic -Wall -c -I.

SRCDIR=src
OPENGL=opengl
UTILS=utils

all: project

project: opengl utils ${FILES}
	$(CC) $(FILES) $(CFLAGS) opengl utils -o shipwreak;

utils: ${SRCDIR}/${UTILS}/utils.c
	$(CC) $(CFLAGS2) ${SRCDIR}/${UTILS}/utils.c -o utils;

opengl: ${SRCDIR}/${OPENGL}/opengl_funcs.c
	$(CC) $(CFLAGS2) ${SRCDIR}/${OPENGL}/opengl_funcs.c -o opengl;

clean:
	rm shipwreak opengl utils