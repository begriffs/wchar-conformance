.POSIX:

CFLAGS = -std=c99 -pedantic -Wall -Wextra
include config.mk

.c:
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

w : w.c
