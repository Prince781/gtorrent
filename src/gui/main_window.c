#include <gtk/gtk.h>
#include "main_window.h"

const char mw_title[] = "gTorrent";
static GtkWidget *main_window;
static GtkWidget *mw_headerbar;

static void headerbar_populate(GtkWidget *);

void gt_gui_main_window_init(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	
	// widget init
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	mw_headerbar = gtk_header_bar_new();
	
	// main window
	gtk_window_set_titlebar(GTK_WINDOW(main_window), mw_headerbar);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 820, 600);
	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit),
			 NULL);
	
	// header bar widget
	gtk_header_bar_set_title(GTK_HEADER_BAR(mw_headerbar), mw_title);
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(mw_headerbar),TRUE);
	headerbar_populate(mw_headerbar);
	
	// add widgets to window

	gtk_widget_show_all(main_window);

	gtk_main();		// start main loop
}

// populate headerbar and initialize
static void headerbar_populate(GtkWidget *hb) {
	GtkWidget *magnet_dl, *pause, *settings;

	// initialize buttons
	magnet_dl = gtk_button_new_from_icon_name("find-location-symbolic",
						  GTK_ICON_SIZE_BUTTON);
	gtk_button_set_focus_on_click(GTK_BUTTON(magnet_dl), FALSE);
	gtk_widget_set_tooltip_text(magnet_dl, "Enter Magnet Link");
	pause = gtk_button_new_from_icon_name("media-playback-start-symbolic",
					      GTK_ICON_SIZE_BUTTON);
	gtk_button_set_focus_on_click(GTK_BUTTON(pause), FALSE);
	gtk_widget_set_sensitive(pause, FALSE);	// disable initially
	settings = gtk_button_new_from_icon_name("format-justify-fill-symbolic",
					      GTK_ICON_SIZE_BUTTON);
	gtk_button_set_focus_on_click(GTK_BUTTON(settings), FALSE);
	gtk_widget_set_tooltip_text(settings, "Settings");
	
	// TODO: set callback functions

	// pack buttons
	gtk_header_bar_pack_start(GTK_HEADER_BAR(hb), magnet_dl);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(hb), pause);
	gtk_header_bar_pack_end(GTK_HEADER_BAR(hb), settings);

	// show
	gtk_widget_show(magnet_dl);
	gtk_widget_show(pause);
	gtk_widget_show(settings);
}
