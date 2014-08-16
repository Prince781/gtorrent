// event_handler.h
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

struct gui_event {
	void *data;		// data to invoke function with
	int (*func)(void *);	// the function
	struct gui_event *next;
};

typedef struct gui_event gui_event;

/* @gt_gui_event_create(): create a new GUI event (to be added to the list),
 * with an optional function and data to provide. */
gui_event		*gt_gui_event_create		(int (*func)(void *),
							 void *data);

/* @gt_gui_event_hook(): hook a unique GUI event to the list. This function
 * returns a non-zero value on success. */
int			gt_gui_event_hook		(gui_event *e);

/* @gt_gui_event_unhook(): remove a GUI event from the list, or return NULL if
 * the event is nonexistent*/
gui_event		*gt_gui_event_unhook		(gui_event *e);

/* @gt_gui_events_invoke(): invoke all events on the list. The number of
 * events returning a non-zero value upon invocation is returned.*/
int			gt_gui_events_invoke		(void);

/* @gt_gui_event_destroy(): destroy a GUI event object */
void			gt_gui_event_destroy		(gui_event *e);

/* @gt_gui_events_destroy_all(): remove and destroy all GUI events from the
 * list. The number of removed elements is returned. */
int			gt_gui_events_destroy_all	(void);

#endif
