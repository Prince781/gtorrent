#include "systray.h"
#include <libnotify/notify.h>

const char stat_app_name[] = "gTorrent";

int gt_gui_systray_start(void) {
	return notify_init(stat_app_name);
}

int gt_gui_systray_notify(const char *summary, const char *body) {
	NotifyNotification *notif;
	extern GdkPixbuf *default_icon;

	notif = notify_notification_new(summary, body, NULL);
	notify_notification_set_app_name(notif, stat_app_name);
	notify_notification_set_icon_from_pixbuf(notif, default_icon);
	
	return notify_notification_show(notif, NULL);
}

void gt_gui_systray_stop(void) {
	notify_uninit();
}


