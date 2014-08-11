// initialize gTorrent and GTK+
#include "../core.h"
#include "../console.h"
#include "main_window.h"
#include "stats.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <time.h>
#include <string.h>

GtkApplication *app;
GdkPixbuf *default_icon, *default_logo;

static void session_start(GApplication *, gpointer);
static void session_stop(GApplication *, gpointer);
static gboolean session_update(gpointer);

// app menu functions
static void app_show_about(GSimpleAction *, GVariant *, gpointer);
static void app_quit(GSimpleAction *, GVariant *, gpointer);

int main(int argc, char *argv[]) {
	int status;
	

	app = gtk_application_new("org.gt.gTorrent", G_APPLICATION_FLAGS_NONE);

	g_signal_connect(app, "startup", G_CALLBACK(session_start), NULL);
	g_signal_connect(app, "activate", G_CALLBACK(gt_gui_activate), NULL);
	g_signal_connect(app, "shutdown", G_CALLBACK(session_stop), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	return status;
}

// session_start: start gtorrent session and add actions
static void session_start(GApplication *app, gpointer user_data) {
	static const GActionEntry app_action_entries[] = {
		{	"about",	app_show_about	},
		{	"quit",		app_quit	},
		{}
	};
	GMenu *app_menu;

	// load pixbufs first
	if ((default_icon = gdk_pixbuf_new_from_resource(
		"/org/gt/gTorrent/gtorrent.png", NULL)) == NULL)
		Console.error("Could not find gtorrent.png");
	else
		gtk_window_set_default_icon(default_icon);
	if ((default_logo = gdk_pixbuf_new_from_resource(
		"/org/gt/gTorrent/gtorrentlogo.png", NULL)) == NULL)
		Console.error("Could not find gtorrentlogo.png");

	Console.debug("Initializing core...");
	gt_core_session_start(GT_CORE_DEFAULT_PORTS());
	gdk_threads_add_timeout(500, session_update, NULL);

	g_action_map_add_action_entries(G_ACTION_MAP(app), app_action_entries,
		-1, NULL);
	app_menu = g_menu_new();
	g_menu_append(app_menu, "About", "app.about");
	g_menu_append(app_menu, "Quit", "app.quit");
	gtk_application_set_app_menu(GTK_APPLICATION(app),
		G_MENU_MODEL(app_menu));
}

// session_update: update gtorrent session
static gboolean session_update(gpointer data) {
	gt_core_session_update();
	gt_gui_stat_update();
	return TRUE;	// TODO: detach if session is invalid
}
// session_stop: stop gtorrent session and end items
static void session_stop(GApplication *app, gpointer user_data) {
	Console.debug("gTorrent terminating...");
	if (default_icon != NULL)
		g_object_unref(default_icon);
	if (default_logo != NULL)
		g_object_unref(default_logo);
	gt_gui_stat_destroy();
	gt_core_session_end();
}

static void app_show_about(GSimpleAction *action, GVariant *p, gpointer data) {
	static const char *authors[] = {
		"Prince781 <princetonf@optonline.net>", NULL
	};
	char year[10], cright[100];
	time_t now = time(NULL);
	
	strftime(year, 10, "%G", localtime(&now));
	snprintf(cright, 100, "Copyright \xc2\xa9 %s The gTorrent Developers",
		 year);
	gtk_show_about_dialog(gtk_application_get_active_window(app),
		"authors", authors,
		"comments", _("A simple torrent client built off of"
			      " libtorrent."),
		"copyright", _(cright),
		"website", "https://github.com/Prince781/gtorrent",
		"website-label", _("Source on GitHub"),
		"license-type", GTK_LICENSE_GPL_2_0,
		"logo", default_logo,
		NULL);
}

static void app_quit(GSimpleAction *action, GVariant *p, gpointer data) {
	g_application_quit(G_APPLICATION(app));
}
