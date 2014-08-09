// stats_graph.c - draw session statistics graphically
#include "../core.h"
#include "../console.h"
#include "stats_graph.h"
#include "stats.h"

gboolean
gt_gui_stats_graph_draw(GtkWidget *canvas, cairo_t *cr, gpointer data) {
	int width, height;
	double x, y;
	double largest = 1.0;
	double damp = 0.7;	// damp height factor
	struct sess_stat *p, *pb;

	if ((p = gt_gui_get_stat()) == NULL)
		return FALSE;

	width = gtk_widget_get_allocated_width(canvas);
	height = gtk_widget_get_allocated_height(canvas);

	cairo_set_line_width(cr, 0.3);

	// draw grid first
	cairo_set_source_rgba(cr, 0.3, 0.3, 0.3, 1.0);
	cairo_rectangle(cr, 15, 15, width-30, height-30);
	cairo_stroke(cr);

	for (y = 15 + (height-30)/4; y < height-15; y += (height-30)/4) {
		cairo_move_to(cr, 15, y);
		cairo_line_to(cr, width-15, y);
		cairo_stroke(cr);
	}

	// draw chart
	cairo_set_line_width(cr, 0.3);
	cairo_set_source_rgb(cr, 0.7, 0.1, 0.3);
	largest = 0;
	for (pb = p; p->next != pb; p = p->next)
		if (p->val > largest)
			largest = p->val;
	p = pb;
	x = 15;
	for (pb = p; p->next != pb; p = p->next) {
		if (p->val < 0)
			break;
		if (x == 15)
			cairo_move_to(cr, x, 
				height-15-damp*(height-30)*(p->val/largest));
		else
			cairo_line_to(cr, x,
				height-15-damp*(height-30)*(p->val/largest));
		x += width / STATSIZE; 
	}

	cairo_stroke(cr);
	return FALSE;
}

gboolean gt_gui_stats_update(gpointer data) {
	if (data == NULL)
		Console.error("%s: widget is null", "gt_gui_stats_update");
	else
		gtk_widget_queue_draw(GTK_WIDGET(data));
	return TRUE;
}
