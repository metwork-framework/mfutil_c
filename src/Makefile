DEBUG=yes
ifeq ($(DEBUG),yes)
	DEBUG_CFLAGS=-g
else
	DEBUG_CFLAGS=-O2 -Os
endif
FORCE_RPATH=
ifeq ($(FORCE_RPATH),)
	FORCE_RPATH_STR=
else
	FORCE_RPATH_STR=-Wl,-rpath=$(FORCE_RPATH)
endif
PREFIX?=/usr/local
CFLAGS+=-D_XOPEN_SOURCE=700

_LDFLAGS=$(LDFLAGS) -L. $(shell pkg-config --libs glib-2.0) $(FORCE_RPATH_STR)
_CFLAGS=$(CFLAGS) -I. $(shell pkg-config --cflags glib-2.0) -fPIC -Wall -std=c99 -Wextra -pedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -DG_LOG_DOMAIN=\"mfutil_c\" $(DEBUG_CFLAGS)

CC=gcc

OBJECTS=wrapper.o field.o mfutil.o
BINARIES=std_redirect _field_prepend _field_remove is_interactive get_unique_hexa_identifier echo_warning echo_ok echo_nok echo_clean echo_running echo_bold
LIBS=libmfutil.so

all: $(OBJECTS) $(BINARIES) $(LIBS) mfutil.pc

clean:
	rm -f $(OBJECTS) $(BINARIES) core.* vgcore.*

mfutil.o: mfutil.c mfutil.h _mfutil.h
	$(CC) -c $(_CFLAGS) -o $@ $<

libmfutil.so: $(OBJECTS)
	$(CC) -shared $(CFLAGS) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

mfutil.pc: mfutil.pc.pc
	cat $< |sed 's|{{PREFIX}}|$(PREFIX)|g' >$@

wrapper.o: wrapper.c wrapper.h
	$(CC) -c $(_CFLAGS) -o $@ $<

field.o: field.c field.h
	$(CC) -c $(_CFLAGS) -o $@ $<

std_redirect: std_redirect.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

echo_clean: echo_clean.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

echo_bold: echo_bold.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

echo_running: echo_running.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

echo_warning: echo_warning.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

echo_ok: echo_ok.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

echo_nok: echo_nok.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

get_unique_hexa_identifier: get_unique_hexa_identifier.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

is_interactive: is_interactive.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

_field_prepend: _field_prepend.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

_field_remove: _field_remove.c $(OBJECTS)
	$(CC) $(_CFLAGS) $(_LDFLAGS) -o $@ $^

install: $(BINARIES) $(LIBS)
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/lib/pkgconfig
	mkdir -p $(PREFIX)/include
	cp -f $(BINARIES) $(PREFIX)/bin/
	cp -f $(LIBS) $(PREFIX)/lib/
	cp -f mfutil.h $(PREFIX)/include/
	cp -f mfutil.pc $(PREFIX)/lib/pkgconfig/

test: all
	./test_std_redirect.sh

leak: all
	$(VALGRIND) ./std_redirect --stdout=test.log -- date && echo "OK"

coverage: all
