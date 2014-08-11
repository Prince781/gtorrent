# Makefile for gTorrent
# note: GUI is disabled at the moment. edit this makefile to enable it
LD          = ld
CC          = gcc
CXX         = g++
CFLAGS      = -ggdb -Wall -O0
LDFLAGS     = `pkg-config --libs libtorrent-rasterbar gtk+-3.0`
BIN         = ../gTorrent
LIBTORRENT  = wrappers/libtorrent.o
GUI         = gui/gui.o

# colors
red         = '\e[0;31m'
green       = '\e[1;32m'
nc          = '\e[0m'

all: gtorrent.o $(LIBTORRENT) $(GUI)
	@echo -e ${green}Building everything...${nc}
	$(CXX) $(CFLAGS) gtorrent.o $(LIBTORRENT) $(GUI) -o $(BIN) $(LDFLAGS)
clean:
	$(RM) *.o $(BIN)
	$(MAKE) clean -C wrappers
	$(MAKE) clean -C gui

# gtorrent.o: console.o core.o torrent.o test.o
gtorrent.o: console.o core.o torrent.o gtorrent.h
	$(LD) -r *.o -o gtorrent.o

# other dependencies
$(LIBTORRENT):
	@echo -e ${green}Building C wrapper for libtorrent-rasterbar...${nc}
	@$(MAKE) -C wrappers

$(GUI):
	@echo -e ${green}Building GTK frontend...${nc}
	@$(MAKE) -C gui

