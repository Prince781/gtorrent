#include "systray.h"
#include "main_window.h"
#include <stdlib.h>

const char stat_icon_name[] = "gtorrent";
GtkStatusIcon *status_icon;

int gt_gui_systray_init(GdkScreen *screen) {
	if (status_icon != NULL)
		return 0;

	extern GdkPixbuf *default_icon;		// window icon for gTorrent
	status_icon = gtk_status_icon_new_from_pixbuf(default_icon);

	if (status_icon == NULL)
		return 0;

	gtk_status_icon_set_screen(status_icon, screen);
	gtk_status_icon_set_title(status_icon, mw_title);
	gtk_status_icon_set_name(status_icon, stat_icon_name);
	gtk_status_icon_set_tooltip_text(status_icon, mw_title);
	return 1;
}
