// torrent_add.h
#ifndef TORRENT_ADD_H
#define TORRENT_ADD_H

#include <gtk/gtk.h>

/* @gt_gui_add_torrent(): create a GtkFileChooserDialog for adding a new
 * torrent */
void gt_gui_add_torrent(GtkButton *button, gpointer data);

/* @gt_gui_add_magnet(): create a new torrent from a magnet link */
void gt_gui_add_magnet(GtkEntry *entry, gpointer data);

#endif
