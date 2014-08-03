# Makefile for gTorrent
LD		= ld
CC		= gcc
CXX		= g++
CFLAGS		= -g -Wall -O0
LDLIBS		= `pkg-config --libs libtorrent-rasterbar gtk+-3.0`
GTORRENT	= ../gTorrent
LTWRAPPER	= wrappers/libtorrent.o
GUILIB		= gui.o

# colors
red		= '\e[0;31m'
green		= '\e[1;32m'
nc		= '\e[0m'

all: gtorrent.o $(LTWRAPPER) $(GUILIB)
	@echo -e ${green}Building everything...${nc}
	$(CXX) $(CFLAGS) gtorrent.o $(LTWRAPPER) $(GUILIB) -o $(GTORRENT) $(LDLIBS)

clean:
	$(RM) *.o $(GTORRENT)
	$(MAKE) clean -C wrappers

gtorrent.o: console.o core.o main.o torrent.o test.o
	$(LD) -r *.o -o gtorrent.o

console.o: console.c console.h
	$(CC) $(CFLAGS) -c console.c

core.o: core.c core.h
	$(CC) $(CFLAGS) -c core.c

torrent.o: torrent.c torrent.h
	$(CC) $(CFLAGS) -c torrent.c

test.o: test.c test.h
	$(CC) $(CFLAGS) -c test.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

# dependencies
$(LTWRAPPER):
	@echo -e ${green}Building C wrapper for libtorrent-rasterbar...${nc}
	@$(MAKE) -C wrappers

$(GUILIB):
	@echo -e ${green}Building GTK frontend...${nc}
	@$(MAKE) -C gui

