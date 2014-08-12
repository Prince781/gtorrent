#include <gtk/gtk.h>
#include "style.h"
#include "../core.h"
#include "../console.h"
#include "torrent_add.h"
#include "main_window.h"
#include "torrent_item.h"
#include "stats_graph.h"

const char mw_title[] = "gTorrent";
GtkWidget *main_window;
GtkWidget *mw_headerbar;
GtkWidget *mw_torrentlist;	// GtkListBox of torrents
GtkWidget *tstats_revealer;	// GtkRevealer around tstats	
GtkWidget *mw_torrentstats;	// GtkGrid containing status widgets
GtkWidget *mwt_title;		// torrent title (stats)
GtkWidget *mwt_info[MWT_SIZE];	// torrent info labels

static void headerbar_populate(GtkWidget *);
static void vbox_populate(GtkWidget *);
static void tlist_update(GtkListBoxRow *, GtkListBoxRow *, gpointer);
static void tlist_update_destroy(gpointer);

void gt_gui_activate(GApplication *app, gpointer user_data) {
	GdkScreen *screen;	// global screen associated with window
	GtkCssProvider *style;	// global css provider
	GtkWidget *vbox;	// inside container after header bar

	// widget init
	main_window = gtk_application_window_new(GTK_APPLICATION(app));
	mw_headerbar = gtk_header_bar_new();
	
	// main window
	gtk_window_set_titlebar(GTK_WINDOW(main_window), mw_headerbar);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 820, 600);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);

	// load CSS
	screen = gtk_window_get_screen(GTK_WINDOW(main_window));
	style = gtk_css_provider_new();
	gtk_css_provider_load_from_data(style, _binary_res_style_css_start,
					-1, NULL);
	gtk_style_context_add_provider_for_screen(screen,
					GTK_STYLE_PROVIDER(style),
					GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	// header bar widget
	gtk_header_bar_set_title(GTK_HEADER_BAR(mw_headerbar), mw_title);
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(mw_headerbar),TRUE);
	headerbar_populate(mw_headerbar);

	// layout containers
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	vbox_populate(vbox);
	
	// add widgets to window
	gtk_container_add(GTK_CONTAINER(main_window), vbox);

	// set update for torrent statistics
	gdk_threads_add_timeout(1000, gt_gui_trnt_post_statistics,
		mw_torrentlist); 

	gtk_widget_show_all(main_window);
}

// populate headerbar and initialize
static void headerbar_populate(GtkWidget *hb) {
	GtkWidget *add_torrent, *magnet_dl, *pause, *settings;
	GtkWidget *magnet_dl_icon;
	GtkWidget *magnet_dl_popover;
	GtkWidget *magnet_dl_entry;

	// initialize buttons
	add_torrent = gtk_button_new_from_icon_name("list-add-symbolic",
						    GTK_ICON_SIZE_BUTTON);
	gtk_button_set_focus_on_click(GTK_BUTTON(add_torrent), FALSE);
	gtk_widget_set_tooltip_text(add_torrent, "Add a torrent");

	magnet_dl = gtk_menu_button_new();
	magnet_dl_icon = gtk_image_new_from_icon_name("edit-paste-symbolic",
						  GTK_ICON_SIZE_BUTTON);
	gtk_button_set_image(GTK_BUTTON(magnet_dl), magnet_dl_icon);
	gtk_button_set_focus_on_click(GTK_BUTTON(magnet_dl), FALSE);
	gtk_widget_set_tooltip_text(magnet_dl, "Enter magnet link");

	// magnet link button - popover
	magnet_dl_popover = gtk_popover_new(magnet_dl);
	gtk_menu_button_set_popover(GTK_MENU_BUTTON(magnet_dl),
				    magnet_dl_popover);
	magnet_dl_entry = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(magnet_dl_entry), 50);
	gtk_widget_set_tooltip_text(magnet_dl_entry, "Enter magnet link");
	gtk_container_add(GTK_CONTAINER(magnet_dl_popover), magnet_dl_entry);
	gtk_widget_show(magnet_dl_entry);

	// pause and settings button
	pause = gtk_button_new_from_icon_name("media-playback-start-symbolic",
					      GTK_ICON_SIZE_BUTTON);
	gtk_button_set_focus_on_click(GTK_BUTTON(pause), FALSE);
	gtk_widget_set_sensitive(pause, FALSE);	// disable initially

	settings = gtk_button_new_from_icon_name("emblem-system-symbolic",
					      GTK_ICON_SIZE_BUTTON);
	gtk_button_set_focus_on_click(GTK_BUTTON(settings), FALSE);
	gtk_widget_set_tooltip_text(settings, "Settings");
	
	// callback functions
	g_signal_connect(add_torrent, "clicked", 
			 G_CALLBACK(gt_gui_add_torrent), NULL);
	g_signal_connect(magnet_dl_entry, "activate",
			 G_CALLBACK(gt_gui_add_magnet), magnet_dl_popover);

	// pack buttons
	gtk_header_bar_pack_start(GTK_HEADER_BAR(hb), add_torrent);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(hb), magnet_dl);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(hb), pause);
	gtk_header_bar_pack_end(GTK_HEADER_BAR(hb), settings);

	// show
	gtk_widget_show_all(hb);
}

// populate vbox with widgets
static void vbox_populate(GtkWidget *vb) {
	GtkWidget *trnt_list_holder;	// scrollable window for box
	GtkWidget *trnt_list_box;	// vertical box

	GtkWidget *trnt_divider;

	GtkWidget *trnt_info;

	GtkWidget *tstats;		// GtkBox around stats
	int l;
	GtkWidget *mwt_label[MWT_SIZE];	// labels for torrent stats
	
	char *labels[MWT_SIZE] = {
		"peers", "upload", "download", "age", "ratio",
		"last activity", "priority"
	};
	GtkWidget *stats_divider;
	GtkWidget *stats_canvas;

	// torrent list holder
	trnt_list_holder = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request(trnt_list_holder, -1, 340);
	gtk_widget_set_name(trnt_list_holder, "trnt_list_holder");

	// torrent list box
	trnt_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_name(trnt_list_box, "trnt_list_box");
	gtk_container_add(GTK_CONTAINER(trnt_list_holder), trnt_list_box);

	// torrent list
	mw_torrentlist = gtk_list_box_new();
	gtk_list_box_set_header_func(GTK_LIST_BOX(mw_torrentlist),
		tlist_update, NULL, tlist_update_destroy);
	gtk_widget_set_name(mw_torrentlist, "mw_torrentlist");

	// add widgets to torrent list holder
	gtk_box_pack_start(GTK_BOX(trnt_list_box), mw_torrentlist, 
			   FALSE, FALSE, 0);

	// add separator
	trnt_divider = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

	// torrent info
	trnt_info = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_size_request(trnt_info, 820, 240);
	gtk_widget_set_name(trnt_info, "trnt_info");

	// torrent statistics and revealer
	tstats_revealer = gtk_revealer_new();
	gtk_revealer_set_transition_type(GTK_REVEALER(tstats_revealer),
				GTK_REVEALER_TRANSITION_TYPE_SLIDE_RIGHT);
	gtk_revealer_set_transition_duration(GTK_REVEALER(tstats_revealer),
				934);
	gtk_box_pack_start(GTK_BOX(trnt_info), tstats_revealer,
			   FALSE, FALSE, 0);

	tstats = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(tstats, 300, -1);
	gtk_widget_set_name(tstats, "tstats");
	gtk_container_add(GTK_CONTAINER(tstats_revealer), tstats);

	// stats - title
	mwt_title = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(mwt_title),
		"<span size=\"large\" weight=\"bold\"></span>");

	gtk_label_set_ellipsize(GTK_LABEL(mwt_title), PANGO_ELLIPSIZE_END);
	gtk_label_set_max_width_chars(GTK_LABEL(mwt_title), 0);	// hack
	/* since gtk_label_set_justify does not work for single-line labels,
 	 * we must use the deprecated (in 3.14) gtk_misc_set_alignment for
 	 * now */
	gtk_misc_set_alignment(GTK_MISC(mwt_title), 0, 0.5);
	gtk_widget_set_halign(mwt_title, GTK_ALIGN_START);
	gtk_widget_set_margin_start(mwt_title, 15);
	gtk_widget_set_margin_end(mwt_title, 15);
	gtk_widget_set_size_request(mwt_title, 270, -1);

	gtk_box_pack_start(GTK_BOX(tstats), mwt_title, TRUE, TRUE, 0);

	// stats - grid
	mw_torrentstats = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(mw_torrentstats), 8);
	gtk_grid_set_column_homogeneous(GTK_GRID(mw_torrentstats), TRUE);
	gtk_widget_set_halign(mw_torrentstats, GTK_ALIGN_FILL);
	gtk_widget_set_margin_start(mw_torrentstats, 30);
	gtk_box_pack_start(GTK_BOX(tstats), mw_torrentstats,
			   TRUE, TRUE, 0);
	for (l=0; l<MWT_SIZE; ++l) {
		mwt_label[l] = gtk_label_new(labels[l]);
		gtk_label_set_justify(GTK_LABEL(mwt_label[l]),
				      GTK_JUSTIFY_LEFT);
		gtk_widget_set_halign(mwt_label[l], GTK_ALIGN_START);
		gtk_grid_attach(GTK_GRID(mw_torrentstats), mwt_label[l],
				0, l+1, 1, 1);

		mwt_info[l] = gtk_label_new(NULL);
		gtk_label_set_justify(GTK_LABEL(mwt_info[l]),
				      GTK_JUSTIFY_CENTER);
		gtk_widget_set_halign(mwt_info[l], GTK_ALIGN_CENTER);
		gtk_grid_attach(GTK_GRID(mw_torrentstats), mwt_info[l],
				1, l+1, 2, 1);
	}

	// separator
	stats_divider = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start(GTK_BOX(trnt_info), stats_divider, FALSE, FALSE, 0);

	// drawing area for session statistics
	stats_canvas = gtk_drawing_area_new();
	g_signal_connect(stats_canvas, "draw",
			 G_CALLBACK(gt_gui_stats_graph_draw), NULL);
	gdk_threads_add_timeout(200, gt_gui_stats_update, stats_canvas); 
	gtk_box_pack_start(GTK_BOX(trnt_info), stats_canvas, TRUE, TRUE, 0);

	// add widgets to vbox
	gtk_box_pack_start(GTK_BOX(vb), trnt_list_holder, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vb), trnt_divider, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vb), trnt_info, FALSE, FALSE, 0);

	// show
	gtk_widget_show_all(vb);

	// hide tstats initially
	gtk_widget_hide(tstats);
}

// hack for lack of :last-child selector support in GtkListBox
static void tlist_update(GtkListBoxRow *row, GtkListBoxRow *before,
			 gpointer data) {
	GtkStyleContext *context;
	GtkCssProvider *style;
	

	context = gtk_widget_get_style_context(GTK_WIDGET(row));
	style = gtk_css_provider_new();
	gtk_css_provider_load_from_data(style,
	before == NULL ?
		"GtkListBoxRow { border-top: 1px solid lighter(@borders); }"
	:	"GtkListBoxRow { border-top: none; }",
	-1, NULL);
	gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(style),
			GTK_STYLE_PROVIDER_PRIORITY_USER);
}

static void tlist_update_destroy(gpointer data) {
	if (data != NULL)
		g_object_unref(data);
}
