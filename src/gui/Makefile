LD		= ld
CC		= gcc
CFLAGS		= -g -Wall -O0
LDFLAGS		= `pkg-config --cflags gtk+-3.0`
LDLIBS		= `pkg-config --libs gtk+-3.0`
OBJ		= gui.o

all: $(OBJ)

clean:
	$(RM) *.o

$(OBJ): main_window.o
	$(LD) -r *.o -o $(OBJ)

main_window.o: main_window.c main_window.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c main_window.c $(LDLIBS)

