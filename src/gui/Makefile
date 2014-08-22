LD		= ld
CC		= gcc
CFLAGS		= -g -Wall -O0
LDFLAGS		= `pkg-config --cflags gtk+-3.0 libnotify`
LDLIBS		= `pkg-config --libs gtk+-3.0 libnotify`
OBJ		= gui.o
OBJECTS		= main_window.o gtk_application_main.o torrent_add.o \
torrent_item.o torrent_properties_window.o stats_graph.o stats.o \
event_handler.o systray.o resources.o style.o

all: $(OBJ)

clean:
	$(RM) *.o

$(OBJ): $(OBJECTS)
	$(LD) -r *.o -o $(OBJ)

systray.o: systray.c systray.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c systray.c $(LDLIBS)

event_handler.o: event_handler.c event_handler.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c event_handler.c $(LDLIBS)

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c stats.c $(LDLIBS)

stats_graph.o: stats_graph.c stats_graph.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c stats_graph.c $(LDLIBS)

torrent_properties_window.o: torrent_properties_window.c torrent_properties_window.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c torrent_properties_window.c $(LDLIBS)

torrent_add.o: torrent_add.c torrent_add.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c torrent_add.c $(LDLIBS)

torrent_item.o: torrent_item.c torrent_item.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c torrent_item.c $(LDLIBS)

main_window.o: main_window.c main_window.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c main_window.c $(LDLIBS)

gtk_application_main.o: gtk_application_main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c gtk_application_main.c $(LDLIBS)

style.o: style.h res/style.css
	$(LD) -r -b binary -o style.o res/style.css

resources.o:
	$(MAKE) -C res
	$(CC) $(CFLAGS) $(LDFLAGS) -c res/resources.c $(LDLIBS)
