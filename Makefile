# Makefile for gTorrent
SRC	= src
DESTDIR = /usr/bin

all:
	$(MAKE) -C $(SRC)

install:
	mkdir -p $(DESTDIR)
	cp gTorrent $(DESTDIR)/gTorrent
	chmod a+x $(DESTDIR)

uninstall:
	$(RM) $(DESTDIR)/gTorrent

clean:
	$(MAKE) clean -C $(SRC)
