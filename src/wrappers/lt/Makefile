LD	= ld
CXX	= g++
CFLAGS	= -g -Wall O0
LDLIBS	= `pkg-config --libs libtorrent-rasterbar`
WRAPPER	= ../libtorrent.o
OBJECTS = lt_session.o lt_torrent.o lt_filestorage.o

$*: $*.h
	$(CXX) $(CFLAGS) -c $@

all: $(OBJECTS)
	$(LD) -r *.o -o $(WRAPPER)

clean:
	$(RM) *.o $(WRAPPER)

