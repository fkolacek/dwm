# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

dwm: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p dwm-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk \
		dwm.1 ${SRC} dwm-${VERSION}
	@tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	@gzip dwm-${VERSION}.tar
	@rm -rf dwm-${VERSION}

install: all
	@echo
	@echo ":: [ DWM core ] ::"
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f dwm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	@echo
	@echo ":: [ DWM session  ] ::"
	@echo installing dwm.desktop to ${XSESSIONS}
	@cp -f scripts/dwm.desktop ${XSESSIONS}/dwm.desktop
	@echo installing dwm-personalized to ${DESTDIR}${PREFIX}/bin
	@cp -f scripts/dwm-personalized ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm-personalized
	@echo
	@echo ":: [ DWM-PANEL ] ::"
	@echo installing dwm-panel to /usr/local/bin
	@cp -f dwm-panel/dwm-panel /usr/local/bin/dwm-panel
	@cp -f dwm-panel/dwm-panel-cycle /usr/local/bin/dwm-panel-cycle
	@chmod +x /usr/local/bin/dwm-panel /usr/local/bin/dwm-panel-cycle
	@echo
	@echo ":: [ SCRIPTS ] ::"
	@echo "Installing 'dwm-open-browser' to ${PREFIX}/bin/dwm-open-browser"
	@sed "s/WEB_BROWSER/${WEB_BROWSER}/g" < scripts/dwm-open-browser > ${DESTDIR}${PREFIX}/bin/dwm-open-browser
	@echo "Installing 'dwm-menu' to ${PREFIX}/bin/dwm-menu"
	@cp -f scripts/dwm-menu ${DESTDIR}${PREFIX}/bin/dwm-menu
	@cp -f scripts/dwm-switch-keyboard ${DESTDIR}${PREFIX}/bin/dwm-switch-keyboard
	@echo
	@echo ":: [ SCRIPTS - permissions ] ::"
	@chmod +x ${DESTDIR}${PREFIX}/bin/dwm-open-browser
	@chmod +x ${DESTDIR}${PREFIX}/bin/dwm-menu
	@chmod +x ${DESTDIR}${PREFIX}/bin/dwm-switch-keyboard


uninstall:
	@echo "Warning! This script is not reliable - does NOT remove all files."
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/dwm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all options clean dist install uninstall
