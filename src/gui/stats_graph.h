// stats_graph.h
#ifndef UI_STATS_GRAPH_H
#define UI_STATS_GRAPH_H

#include <gtk/gtk.h>

/* @gt_gui_stats_graph_draw(): draw callback for canvas */
gboolean gt_gui_stats_graph_draw(GtkWidget *canvas, cairo_t *cr, gpointer);

/* @gt_gui_stats_graph_update(): interval update function for session */
int gt_gui_stats_update(void *data);

#endif
