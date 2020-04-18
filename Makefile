.POSIX:

CFLAGS = -std=c99 -pedantic -Wall -Wextra
include config.mk

w : w.c
