#ifndef SYSTRAY_H
#define SYSTRAY_H

extern const char stat_app_name[];

/* @gt_gui_systray_init(): initialize the systray icon and set up
 * notifications. Returns a nonzero value on success. */
int			gt_gui_systray_start		(void);

/* @gt_gui_systray_notify(): show a notification. Returns a nonzero value on
 * success. */
int			gt_gui_systray_notify		(const char *summary,
							 const char *body);

/* @gt_gui_systray_stop(); stops the systray icon and notification interface */
void			gt_gui_systray_stop		(void);

#endif
