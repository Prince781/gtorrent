// torrent_item.h
#include "../core.h"
#include "../torrent.h"
#include <gtk/gtk.h>

typedef struct _trnt_widgets {	// holds widgets pertaining to a torrent
	GtkButton	*pause;		// pause button
	GtkLabel	*name;		// torrent name (label)
	GtkLabel	*payload;	// amount downloaded (label)
	GtkLabel	*eta;		// ETA (label)
	GtkProgressBar	*progress;	// progress bar
} trnt_widgets;

/* @gt_gui_add_torrent_item: add torrent item to listbox */
void gt_gui_add_torrent_item(GtkListBox *listbox, gt_torrent *gtp);

/* @trnt_post_statistics(): show additional torrent statistics for the
 * selected torrent widget */
gboolean gt_gui_trnt_post_statistics(gpointer);
