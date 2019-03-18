DEBUG=yes
ifeq ($(DEBUG),yes)
	DEBUG_CFLAGS=-g
else
	DEBUG_CFLAGS=-O2 -Os
endif
PREFIX=/usr/local


_LDFLAGS=$(LDFLAGS) -L. $(shell pkg-config --libs glib-2.0)
_CFLAGS=$(CFLAGS) -I. $(shell pkg-config --cflags glib-2.0) -fPIC -Wall -std=c99 -Wextra -pedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -DG_LOG_DOMAIN=\"mfutil_c\" $(DEBUG_CFLAGS)

CC=gcc

OBJECTS=wrapper.o field.o
BINARIES=std_redirect _field_prepend _field_remove

all: $(OBJECTS) $(BINARIES)

clean:
	rm -f $(OBJECTS) $(BINARIES) core.* vgcore.*

wrapper.o: wrapper.c wrapper.h
	$(CC) -c $(_CFLAGS) -o $@ $<

field.o: field.c field.h
	$(CC) -c $(_CFLAGS) -o $@ $<

std_redirect: std_redirect.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

_field_prepend: _field_prepend.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

_field_remove: _field_remove.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

install:
	mkdir -p $(PREFIX)/bin
	cp -f $(BINARIES) $(PREFIX)/bin/

test: all
	./test_std_redirect.sh
