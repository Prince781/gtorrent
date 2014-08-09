// initialize gTorrent and GTK+
#include "../core.h"
#include "../console.h"
#include "main_window.h"
#include "stats.h"
#include <gtk/gtk.h>

GtkApplication *app;

static void session_start(GApplication *, gpointer);
static void session_stop(GApplication *, gpointer);
static gboolean session_update(gpointer);

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

// session_start: start gtorrent session
static void session_start(GApplication *app, gpointer user_data) {
	Console.debug("Initializing core...");
	gt_core_session_start(GT_CORE_DEFAULT_PORTS());
	gdk_threads_add_timeout(500, session_update, NULL);
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
	gt_core_session_end();
	gt_gui_stat_destroy();
}

