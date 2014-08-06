#include <gtk/gtk.h>

const char mw_title[] = "gTorrent";
GtkWidget *main_window;
GtkWidget *mw_headerbar;

static void headerbar_populate(GtkWidget *);
static void vbox_populate(GtkWidget *);

void gt_gui_activate(GApplication *app, gpointer user_data) {
	GtkWidget *vbox;	// inside container after header bar

	// widget init
	main_window = gtk_application_window_new(GTK_APPLICATION(app));
	mw_headerbar = gtk_header_bar_new();
	
	// main window
	gtk_window_set_titlebar(GTK_WINDOW(main_window), mw_headerbar);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 820, 600);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	
	// header bar widget
	gtk_header_bar_set_title(GTK_HEADER_BAR(mw_headerbar), mw_title);
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(mw_headerbar),TRUE);
	headerbar_populate(mw_headerbar);

	// layout containers
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	vbox_populate(vbox);
	
	// add widgets to window
	gtk_container_add(GTK_CONTAINER(main_window), vbox);

	gtk_widget_show_all(main_window);
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
	gtk_widget_show_all(hb);
}

// populate vbox with widgets
static void vbox_populate(GtkWidget *vb) {
	GtkWidget *trnt_list_holder;	// scrollable window for box
	GtkWidget *trnt_list_box;	// actual box
	GtkStyleContext *tlb_context;
	GtkCssProvider *tlb_style;

	GtkWidget *torrent_list;
	GtkWidget *tlist_item[10];	// for testing
	int i;
	GtkWidget *trnt_info;
	GtkStyleContext *ti_context;
	GtkCssProvider *ti_style;

	// torrent list holder and box
	trnt_list_holder = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request(trnt_list_holder, 820, 340);
	trnt_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(trnt_list_holder), trnt_list_box);

	tlb_context = gtk_widget_get_style_context(trnt_list_box);
	tlb_style = gtk_css_provider_new();
	gtk_css_provider_load_from_data(tlb_style,
	"GtkBox {"
//	"	background-color: rgb(215,218,215);"
	"	background-image: url(\"res/noise_overlay.png\");"
//	"	box-shadow: inset 0 -3px 8px rgba(115,118,115,0.3);"
	"}",
	-1, NULL);
	gtk_style_context_add_provider(tlb_context,
				GTK_STYLE_PROVIDER(tlb_style),
				GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	// torrent list
	torrent_list = gtk_list_box_new();
	gtk_widget_set_margin_start(torrent_list, 100);
	gtk_widget_set_margin_end(torrent_list, 100);
	
	// for testing purposes
	for (i=0; i<10; ++i) {
		tlist_item[i] = gtk_list_box_row_new();
		gtk_widget_set_size_request(tlist_item[i], -1, 60);
		gtk_list_box_prepend(GTK_LIST_BOX(torrent_list), tlist_item[i]);
	}

	// add widgets to torrent list box
	gtk_box_pack_start(GTK_BOX(trnt_list_box), torrent_list, 
			   FALSE, FALSE, 80);

	// torrent info
	trnt_info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(trnt_info, 820, 180);

	ti_context = gtk_widget_get_style_context(trnt_info);
	ti_style = gtk_css_provider_new();
	gtk_css_provider_load_from_data(ti_style,
	"GtkBox {"
	"	background-color: rgb(241,242,241);"
	// TODO: get outset box-shadow to work for this GtkBox
	"	box-shadow: 0 3px 8px rgba(115,118,115,0.3);"
	"}",
	-1, NULL);
	gtk_style_context_add_provider(ti_context,
				       GTK_STYLE_PROVIDER(ti_style),
				       GTK_STYLE_PROVIDER_PRIORITY_USER);

	// add widgets to vbox
	gtk_box_pack_start(GTK_BOX(vb), trnt_list_holder, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vb), trnt_info, TRUE, TRUE, 0);

	// show
	gtk_widget_show_all(vb);
}
