#include <gtk/gtk.h>
#include "main_window.h"

static GtkWidget *main_window;

void gt_gui_main_window_init(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(main_window), "gTorrent");
	
	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit),
			 NULL);
	gtk_widget_show(main_window);

	gtk_main();
}
