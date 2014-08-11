#include "torrent_item.h"
#include "../core.h"
#include "../console.h"
#include "../torrent.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gi18n.h>

void gt_gui_add_torrent(GtkButton *button, gpointer data) {
	extern GtkWidget *main_window, *mw_torrentlist;
	GtkWidget *chooser;

	chooser = gtk_file_chooser_dialog_new("Open",
			GTK_WINDOW(main_window),
			GTK_FILE_CHOOSER_ACTION_OPEN,
			_("_Cancel"), GTK_RESPONSE_CANCEL,
			_("_Open"), GTK_RESPONSE_ACCEPT,
			NULL);
	gint result = gtk_dialog_run(GTK_DIALOG(chooser));

	// add a new torrent if successful
	if (result == GTK_RESPONSE_ACCEPT) {
		char *fname = gtk_file_chooser_get_filename(
				GTK_FILE_CHOOSER(chooser));
		gt_torrent *gtp = gt_trnt_create(fname, NULL);
		if (gtp != NULL)
			gt_gui_add_torrent_item(GTK_LIST_BOX(mw_torrentlist),
						gtp);
		g_free(fname);
	}

	gtk_widget_destroy(chooser);
}

void gt_gui_add_magnet(GtkEntry *entry, gpointer data) {
	extern GtkWidget *mw_torrentlist;
	GtkWidget *popover = (GtkWidget *) data;
	gt_torrent *gtp;
	const char *link;

	if (!gt_core_is_maglink(link = gtk_entry_get_text(entry)))
		Console.error("\"%s\": not a magnet link", link);
	else {
		gtp = gt_trnt_create(link, NULL);
		if (gtp != NULL)
			gt_gui_add_torrent_item(GTK_LIST_BOX(mw_torrentlist),
						gtp);
	}

	gtk_widget_hide(popover);
}
