// event_handler.c
#include "event_handler.h"
#include <stdlib.h>

static gui_event base = { NULL, NULL };		// start of gui event list

gui_event *gt_gui_event_create(int (*func)(void *), void *data) {
	gui_event *e;

	e = (gui_event *) malloc(sizeof(gui_event));

	e->data = data;
	e->func = func;
	e->next = NULL;

	return e;
}

int gt_gui_event_hook(gui_event *e) {
	gui_event *ep;

	for (ep = &base; ep->next != NULL; ep = ep->next)
		if (ep == e)
			return 0;		// duplicate
	
	ep->next = e;
	return 1;
}

gui_event *gt_gui_event_unhook(gui_event *e) {
	gui_event *ep;

	for (ep = &base; ep->next != e; ep = ep->next)
		if (ep->next == NULL)
			return NULL;

	ep->next = ep->next->next;
	return e;
}

int gt_gui_events_invoke(void) {
	gui_event *ep;
	int total = 0;

	for (ep = &base; ep != NULL; ep = ep->next)
		if (ep->func != NULL)
			total += !!ep->func(ep->data);

	return total;
}

void gt_gui_event_destroy(gui_event *e) {
	free(e);
}

int gt_gui_events_destroy_all(void) {
	int removed = 0;

	for (; base.next != NULL; ++removed)
		gt_gui_event_destroy(gt_gui_event_unhook(base.next));

	return removed;
}
