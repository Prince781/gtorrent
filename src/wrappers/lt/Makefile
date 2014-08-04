LD	= ld
CXX	= g++
CFLAGS	= -g -Wall O0
LDLIBS	= `pkg-config --libs libtorrent-rasterbar`
WRAPPER	= ../libtorrent.o
OBJECTS = session.o torrent.o filestorage.o alerttypes.o

$*: $*.h
	$(CXX) $(CFLAGS) -c $@

all: $(OBJECTS)
	$(LD) -r *.o -o $(WRAPPER)

clean:
	$(RM) *.o $(WRAPPER)

