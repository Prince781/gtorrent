# Makefile for gTorrent
SRC	= src
PRGRM	= /usr/bin/gTorrent

all:
	$(MAKE) -C $(SRC)

install:
	cp gTorrent $(PRGRM)
	chmod a+x $(PRGRM)

uninstall:
	$(RM) $(PRGRM)

clean:
	$(MAKE) clean -C $(SRC)
