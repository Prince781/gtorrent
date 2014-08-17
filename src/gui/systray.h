#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <gtk/gtk.h>

extern const char stat_icon_name[];
extern GtkStatusIcon *status_icon;

/* @gt_gui_systray_init(): initialize the systray icon (GtkStatusIcon) from a
 * given GdkScreen. Returns a nonzero value on success. */
int			gt_gui_systray_init		(GdkScreen *screen);

#endif
