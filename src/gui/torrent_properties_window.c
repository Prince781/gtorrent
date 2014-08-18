#include "../core.h"
#include "../console.h"
#include "torrent_properties_window.h"
#include <gtk/gtk.h>
#include <string.h>
#include <glib.h>
#include <glib/gi18n.h>

void gt_gui_show_torrent_properties(gt_torrent *gtp) {
	extern GtkWidget *main_window;
	GtkWidget *dialog, *body;
	GtkWidget *box;

	GtkWidget *speedheader;
	GtkWidget *speed_option[3];	// HBoxes for options
	GtkWidget *limit_dlspeed_chkbox;
	GtkWidget *limit_dlspeed_label;
	GtkWidget *limit_dlspeed_spin;
	GtkWidget *limit_upspeed_chkbox;
	GtkWidget *limit_upspeed_label;
	GtkWidget *limit_upspeed_spin;
	GtkWidget *priority_label;
	GtkWidget *priority_spin;

	GtkWidget *peerheader;
	GtkWidget *peer_option[2];	// HBoxes for peer options
	GtkWidget *limit_maxpeers_chkbox;
	GtkWidget *limit_maxpeers_label;
	GtkWidget *limit_maxpeers_spin;
	GtkWidget *superseeding_label;
	GtkWidget *superseeding_switch;

	static char title[200];
	torrent_status *status;
	int download_limit, upload_limit, priority, peer_limit;
	bool super_seeding;
	gint response;

	status = lt_trnt_handle_get_status(gtp->th);
	priority = status->priority;
	upload_limit = lt_trnt_handle_get_upload_limit(gtp->th);
	download_limit = lt_trnt_handle_get_download_limit(gtp->th);
	peer_limit = status->connections_limit;
	super_seeding = status->super_seeding;
	snprintf(title, 200, "Properties for %s", status->name);
	dialog = gtk_dialog_new_with_buttons(title, GTK_WINDOW(main_window),
		GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT
		| GTK_DIALOG_USE_HEADER_BAR,
		_("_Okay"), GTK_RESPONSE_OK,
		_("_Cancel"), GTK_RESPONSE_CANCEL,
		NULL);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
	body = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

	// add widgets to dialog
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_widget_set_margin_top(box, 20);
	gtk_widget_set_margin_bottom(box, 20);
	gtk_widget_set_margin_start(box, 40);
	gtk_widget_set_margin_end(box, 40);
	gtk_container_add(GTK_CONTAINER(body), box);
	
	// speed options
	speedheader = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(speedheader),
			     "<span font_weight=\"bold\">Speed</span>");
	gtk_widget_set_halign(speedheader, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(box), speedheader, FALSE, FALSE, 0);

	speed_option[0] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_box_pack_start(GTK_BOX(box), speed_option[0], FALSE, FALSE, 0);
	limit_dlspeed_chkbox = gtk_check_button_new();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(limit_dlspeed_chkbox),
				download_limit > 0);
	gtk_widget_set_margin_start(limit_dlspeed_chkbox, 20);
	gtk_box_pack_start(GTK_BOX(speed_option[0]), limit_dlspeed_chkbox,
			   FALSE, FALSE, 0);
	limit_dlspeed_label = gtk_label_new("Limit download speed (KB/s):");
	gtk_widget_set_size_request(limit_dlspeed_label, 200, -1);
	gtk_widget_set_halign(limit_dlspeed_label, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(speed_option[0]), limit_dlspeed_label,
			   TRUE, TRUE, 0);
	limit_dlspeed_spin = gtk_spin_button_new_with_range(0, 5000, 5);
	if (download_limit > 0)
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(limit_dlspeed_spin),
			(int)(download_limit+512)/1024);
	gtk_box_pack_start(GTK_BOX(speed_option[0]), limit_dlspeed_spin,
			   TRUE, TRUE, 0);
	speed_option[1] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_box_pack_start(GTK_BOX(box), speed_option[1], FALSE, FALSE, 0);
	limit_upspeed_chkbox = gtk_check_button_new();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(limit_upspeed_chkbox),
				     upload_limit > 0);
	gtk_widget_set_margin_start(limit_upspeed_chkbox, 20);
	gtk_box_pack_start(GTK_BOX(speed_option[1]), limit_upspeed_chkbox,
			   FALSE, FALSE, 0);
	limit_upspeed_label = gtk_label_new("Limit upload speed (KB/s):");
	gtk_widget_set_size_request(limit_upspeed_label, 200, -1);
	gtk_widget_set_halign(limit_upspeed_label, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(speed_option[1]), limit_upspeed_label,
			   TRUE, TRUE, 0);
	limit_upspeed_spin = gtk_spin_button_new_with_range(0, 5000, 5);
	if (upload_limit > 0)
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(limit_upspeed_spin),
			(int)(upload_limit+512)/1024);
	gtk_box_pack_start(GTK_BOX(speed_option[1]), limit_upspeed_spin,
			   TRUE, TRUE, 0);
	speed_option[2] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_box_pack_start(GTK_BOX(box), speed_option[2], FALSE, FALSE, 0);
	priority_label = gtk_label_new("Torrent priority:");
	gtk_widget_set_size_request(priority_label, 248, -1);
	gtk_widget_set_halign(priority_label, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(speed_option[2]), priority_label,
			   TRUE, TRUE, 0);
	priority_spin = gtk_spin_button_new_with_range(0, 255, 1);
	gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(priority_spin), TRUE);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(priority_spin), priority);
	gtk_box_pack_start(GTK_BOX(speed_option[2]), priority_spin,
			   TRUE, TRUE, 0);

	// peer options
	peerheader = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(peerheader),
			     "<span font_weight=\"bold\">Peers</span>");
	gtk_widget_set_margin_top(peerheader, 20);
	gtk_widget_set_halign(peerheader, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(box), peerheader, FALSE, FALSE, 0);

	peer_option[0] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_box_pack_start(GTK_BOX(box), peer_option[0], FALSE, FALSE, 0);
	limit_maxpeers_chkbox = gtk_check_button_new();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(limit_maxpeers_chkbox),
				     peer_limit != -1);
	gtk_widget_set_margin_start(limit_maxpeers_chkbox, 20);
	gtk_box_pack_start(GTK_BOX(peer_option[0]), limit_maxpeers_chkbox,
			   FALSE, FALSE, 0);
	limit_maxpeers_label = gtk_label_new("Limit maximum peers:");
	gtk_widget_set_size_request(limit_maxpeers_label, 200, -1);
	gtk_widget_set_halign(limit_maxpeers_label, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(peer_option[0]), limit_maxpeers_label,
			   TRUE, TRUE, 0);
	limit_maxpeers_spin = gtk_spin_button_new_with_range(2, 5000, 1);
	if (peer_limit != -1)
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(limit_maxpeers_spin),
					  peer_limit);
	gtk_box_pack_start(GTK_BOX(peer_option[0]), limit_maxpeers_spin,
			   TRUE, TRUE, 0);

	peer_option[1] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_box_pack_start(GTK_BOX(box), peer_option[1], FALSE, FALSE, 0);
	superseeding_label = gtk_label_new("Super seeding");
	gtk_label_set_justify(GTK_LABEL(superseeding_label),
			      GTK_JUSTIFY_LEFT);
	gtk_widget_set_size_request(superseeding_label, 200, -1);
	gtk_widget_set_halign(superseeding_label, GTK_ALIGN_START);
	gtk_widget_set_margin_start(superseeding_label, 20);
	gtk_box_pack_start(GTK_BOX(peer_option[1]), superseeding_label,
			   TRUE, TRUE, 0);
	superseeding_switch = gtk_switch_new();
	gtk_switch_set_active(GTK_SWITCH(superseeding_switch),
			     super_seeding);
	gtk_widget_set_halign(superseeding_switch, GTK_ALIGN_END);
	gtk_box_pack_end(GTK_BOX(peer_option[1]), superseeding_switch,
			 FALSE, FALSE, 0);

	gtk_widget_show_all(body);
	gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
	response = gtk_dialog_run(GTK_DIALOG(dialog));
	if (response == GTK_RESPONSE_OK) {
		download_limit = gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(limit_dlspeed_chkbox)) ?
			(int) 1024*gtk_spin_button_get_value(
				GTK_SPIN_BUTTON(limit_dlspeed_spin)) : -1;
		upload_limit = gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(limit_upspeed_chkbox)) ?
			(int) 1024*gtk_spin_button_get_value(
				GTK_SPIN_BUTTON(limit_upspeed_spin)) : -1;
		priority = (int) gtk_spin_button_get_value(
				GTK_SPIN_BUTTON(priority_spin));
		peer_limit = gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(limit_maxpeers_chkbox)) ?
			(int) gtk_spin_button_get_value(
				GTK_SPIN_BUTTON(limit_maxpeers_spin)) : -1;
		super_seeding = gtk_switch_get_active(
				GTK_SWITCH(superseeding_switch));
		lt_trnt_handle_set_download_limit(gtp->th, download_limit);
		lt_trnt_handle_set_upload_limit(gtp->th, upload_limit);
		lt_trnt_handle_set_priority(gtp->th, priority);
		lt_trnt_handle_set_max_connections(gtp->th, peer_limit);
		lt_trnt_handle_set_super_seeding(gtp->th, super_seeding);
	}
	
	gtk_widget_destroy(dialog);
}


