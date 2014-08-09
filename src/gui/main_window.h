#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <gtk/gtk.h>

extern const char mw_title[];

#define MWT_SIZE	7	// size of main window torrent stats

/* @gt_gui_activate(): initialize main window of GUI */
void gt_gui_activate(GApplication *app, gpointer user_data);

#endif
