# Makefile for gTorrent
# note: GUI is disabled at the moment. edit this makefile to enable it
LD		= ld
CC		= gcc
CXX		= g++
CFLAGS		= -g -Wall -O0
LDLIBS		= `pkg-config --libs libtorrent-rasterbar gtk+-3.0`
GTORRENT	= ../gTorrent
LTWRAPPER	= wrappers/libtorrent.o
#GUILIB		= gui/gui.o

# colors
red		= '\e[0;31m'
green		= '\e[1;32m'
nc		= '\e[0m'

# all: gtorrent.o $(LTWRAPPER) $(GUILIB)
all: gtorrent.o $(LTWRAPPER)
	@echo -e ${green}Building everything...${nc}
#	$(CXX) $(CFLAGS) gtorrent.o $(LTWRAPPER) $(GUILIB) -o $(GTORRENT) $(LDLIBS)
	$(CXX) $(CFLAGS) gtorrent.o $(LTWRAPPER) -o $(GTORRENT) $(LDLIBS)
clean:
	$(RM) *.o $(GTORRENT)
	$(MAKE) clean -C wrappers
#	$(MAKE) clean -C gui

gtorrent.o: console.o core.o torrent.o test.o
	$(LD) -r *.o -o gtorrent.o

console.o: console.c console.h
	$(CC) $(CFLAGS) -c console.c

core.o: core.c core.h alerts.h
	$(CC) $(CFLAGS) -c core.c

torrent.o: torrent.c torrent.h alerts.h
	$(CC) $(CFLAGS) -c torrent.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

# dependencies
$(LTWRAPPER):
	@echo -e ${green}Building C wrapper for libtorrent-rasterbar...${nc}
	@$(MAKE) -C wrappers

#$(GUILIB):
#	@echo -e ${green}Building GTK frontend...${nc}
#	@$(MAKE) -C gui

