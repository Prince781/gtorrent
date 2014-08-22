// torrent_add.h
#ifndef TORRENT_ADD_H
#define TORRENT_ADD_H

#include <gtk/gtk.h>
#include "../torrent.h"

struct gtrnt_holder {
	gt_torrent		*trnt;
	struct gtrnt_holder	*prev;
};

typedef struct gtrnt_holder gtrnt_holder;

/* @gt_gui_trnt_add_to_queue(): adds a gt_torrent to the pending list */
void	gt_gui_trnt_add_to_queue	(gt_torrent *t);

/* @gt_gui_trnt_add_all(): pops all torrents from the list and adds them. The
 * number of torrents added is returned. */
int	gt_gui_trnt_add_all		(void);

/* @gt_gui_trnt_destroy_all): destroys all items in the queue, calling their
 * proper destructors. The number of items destroyed is returned. */
int	gt_gui_trnt_destroy_all		(void);

/* @gt_gui_add_torrent(): create a GtkFileChooserDialog for adding a new
 * torrent */
void	gt_gui_add_torrent		(GtkButton *button, gpointer data);

/* @gt_gui_add_magnet(): create a new torrent from a magnet link */
void	gt_gui_add_magnet		(GtkEntry *entry, gpointer data);

#endif
