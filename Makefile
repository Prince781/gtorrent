# Makefile for gTorrent
SRC	= src

all:
	$(MAKE) -C $(SRC)

clean:
	$(MAKE) clean -C $(SRC)
