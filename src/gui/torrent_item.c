// torrent_item.c
#include <stdlib.h>
#include <gio/gio.h>
#include <glib.h>
#include "torrent_item.h"
#include "torrent_properties_window.h"
#include "../console.h"
#include <string.h>

/* @trnt_pause_toggle(): toggle paused state of torrent */
static void trnt_pause_toggle(GtkButton *, gpointer);

/* @trnt_show_properties(): show properties dialog of torrent */
static void trnt_show_properties(GSimpleAction *, GVariant *, gpointer);

/* @trnt_open_folder(): open folder of torrent location */
static void trnt_open_folder(GSimpleAction *, GVariant *, gpointer);

/* @trnt_update(): post update messages for torrent */
static int trnt_update(gt_alert *);

/* @trnt_item_destroy(): cause widgets and torrent object to destroy */
static void trnt_item_destroy(GtkButton *, gpointer);

/* @trnt_destroy(): destroy gt_torrent object upon widget destruction */
static void trnt_destroy(gpointer);

void gt_gui_add_torrent_item(GtkListBox *listbox, gt_torrent *gtp) {
	if (! gt_core_session_add_torrent(gtp)) {
		gt_trnt_destroy(gtp);
		return;
	}

	trnt_widgets *widgets = malloc(sizeof(trnt_widgets));

	GtkWidget *row;
	GtkWidget *box;			// container for everything

	GtkWidget *pause_button;

	GtkWidget *center_box;
	GtkWidget *trnt_name;		// name of torrent

	GtkWidget *trnt_status;		// box containing two labels
	GtkWidget *trnt_payload;	// eg. "13 MB of 25 MB" label
	GtkWidget *trnt_eta;		// eg. "1 min, 24 sec" label

	GtkWidget *trnt_progress;	// progress bar
	
	GtkWidget *options_button;	// torrent options
	GtkWidget *options_icon;

	static const GActionEntry options_entries[] = {
		{	"properties",	trnt_show_properties	},
		{	"open_folder",	trnt_open_folder	},
		{}
	};
	GMenu *options_menu;		// options menu
	GSimpleActionGroup *options_actions;

	GtkWidget *delete_button;

	// row and main container
	row = gtk_list_box_row_new();
	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
	gtk_container_add(GTK_CONTAINER(row), box);

	// pause button
	pause_button = gtk_button_new_from_icon_name(
		"media-playback-start-symbolic", GTK_ICON_SIZE_BUTTON);
	gtk_widget_set_tooltip_text(pause_button, "Pause downloading");

	g_signal_connect(pause_button, "clicked",
			 G_CALLBACK(trnt_pause_toggle), gtp);

	gtk_widget_set_margin_start(pause_button, 15);
	gtk_widget_set_margin_top(pause_button, 10);
	gtk_widget_set_margin_bottom(pause_button, 10);
	gtk_box_pack_start(GTK_BOX(box), pause_button, FALSE, FALSE, 0);

	// center box
	center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(center_box, 400, -1);
	gtk_box_pack_start(GTK_BOX(box), center_box, TRUE, TRUE, 0);
	
	// center box: torrent name
	trnt_name = gtk_label_new( lt_trnt_params_get_name(gtp->tp) );
	gtk_label_set_ellipsize(GTK_LABEL(trnt_name), PANGO_ELLIPSIZE_MIDDLE);
	gtk_widget_set_halign(trnt_name, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(center_box), trnt_name, TRUE, TRUE, 0);
	
	// center box: torrent status (box)
	trnt_status = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(center_box), trnt_status, TRUE, TRUE, 0);

	// torrent status: payload
	trnt_payload = gtk_label_new("");
	gtk_widget_set_halign(trnt_payload, GTK_ALIGN_START);
	gtk_label_set_justify(GTK_LABEL(trnt_payload), GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(trnt_status), trnt_payload, TRUE, TRUE, 0);

	// torrent status: ETA
	trnt_eta = gtk_label_new("ETA");
	gtk_widget_set_halign(trnt_eta, GTK_ALIGN_END);
	gtk_label_set_justify(GTK_LABEL(trnt_eta), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_end(GTK_BOX(trnt_status), trnt_eta, TRUE, TRUE, 0);

	// center box: torrent progress
	trnt_progress = gtk_progress_bar_new();
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(trnt_progress), 0.0);
	gtk_box_pack_end(GTK_BOX(center_box), trnt_progress, TRUE, FALSE, 0);

	// options button
	options_button = gtk_menu_button_new();
	options_icon = gtk_image_new_from_icon_name(
		"emblem-system-symbolic", GTK_ICON_SIZE_MENU);
	gtk_button_set_image(GTK_BUTTON(options_button), options_icon);
	gtk_widget_set_tooltip_text(options_button, "Torrent options");
	gtk_widget_set_margin_top(options_button, 10);
	gtk_widget_set_margin_bottom(options_button, 10);

	// options button - menu
	gtk_menu_button_set_use_popover(GTK_MENU_BUTTON(options_button), TRUE);
	options_menu = g_menu_new();
	g_menu_append(options_menu, "Properties", "topts.properties");
	g_menu_append(options_menu, "Open Folder", "topts.open_folder");
	options_actions = g_simple_action_group_new();
	g_action_map_add_action_entries(G_ACTION_MAP(options_actions),
				options_entries, -1, (gpointer) gtp);
	gtk_widget_insert_action_group(options_button, "topts",
				       G_ACTION_GROUP(options_actions));
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(options_button),
				       G_MENU_MODEL(options_menu));

	gtk_box_pack_start(GTK_BOX(box), options_button, FALSE, FALSE, 0);

	// delete button
	delete_button = gtk_button_new_from_icon_name(
		"user-trash-symbolic", GTK_ICON_SIZE_BUTTON);
	gtk_widget_set_tooltip_text(delete_button, "Remove");
	gtk_widget_set_margin_top(delete_button, 10);
	gtk_widget_set_margin_bottom(delete_button, 10);
	gtk_widget_set_margin_end(delete_button, 15);
	gtk_widget_set_can_default(delete_button, TRUE);

	g_signal_connect(delete_button, "clicked",
			 G_CALLBACK(trnt_item_destroy), row);

	gtk_box_pack_end(GTK_BOX(box), delete_button, FALSE, FALSE, 0);

	// add torrent association
	widgets->pause = GTK_BUTTON(pause_button);
	widgets->name = GTK_LABEL(trnt_name);
	widgets->payload = GTK_LABEL(trnt_payload);
	widgets->eta = GTK_LABEL(trnt_eta);
	widgets->progress = GTK_PROGRESS_BAR(trnt_progress);
	gtp->data = (void *) widgets;

	g_object_set_data_full(G_OBJECT(row), "torrent", (gpointer) gtp,
			       trnt_destroy);

	// append widget
	gtk_list_box_prepend(listbox, row);
	gtk_widget_show_all(GTK_WIDGET(listbox));

	// set callback
	gtp->call = trnt_update;
}

gboolean gt_gui_trnt_post_statistics(gpointer listbox) {
	extern GtkWidget *tstats_revealer;
	extern GtkWidget *mwt_title;
	extern GtkWidget *mwt_info[];
	GList *selected;
	gt_torrent *gtp;
	torrent_status *status;
	static char buf[1024];
	int b = 1024;
	uint64_t age;

	selected = gtk_list_box_get_selected_rows(GTK_LIST_BOX(listbox));

	// we are only concerned with first element of linked list
	if (selected != NULL) {
		gtp = (gt_torrent *) g_object_get_data(
				G_OBJECT(selected->data), "torrent");
		if (gtp == NULL) {
			Console.error("%s: could not get torrent stats",
				      "trnt_post_statistics");
			g_list_free(selected);
			return TRUE;
		}
		// reveal if hidden
		if (!gtk_revealer_get_reveal_child(
			GTK_REVEALER(tstats_revealer)))
			gtk_revealer_set_reveal_child(
				GTK_REVEALER(tstats_revealer), TRUE);

		status = lt_trnt_handle_get_status(gtp->th);
		snprintf(buf, b-7, "<span size=\"large\" weight=\"bold\">%s",
			 status->name);
		strcat(buf, "</span>");
		gtk_label_set_label(GTK_LABEL(mwt_title), buf);
		snprintf(buf, b, "%d out of %d", status->num_peers,
						   status->num_connections);
		gtk_label_set_label(GTK_LABEL(mwt_info[0]), buf);
		gt_trnt_getrate(status->upload_payload_rate, buf);
		gtk_label_set_label(GTK_LABEL(mwt_info[1]), buf);
		gt_trnt_getrate(status->download_payload_rate, buf);
		gtk_label_set_label(GTK_LABEL(mwt_info[2]), buf);
		age = (uint64_t) difftime(time(NULL), status->added_time);
		gt_trnt_geteta_fmt(buf, age);
		gtk_label_set_label(GTK_LABEL(mwt_info[3]), buf);
		snprintf(buf, b, "%.3f", (double) status->all_time_upload
		/ (status->all_time_download ? status->all_time_download : 1));
		gtk_label_set_label(GTK_LABEL(mwt_info[4]), buf);
		gt_trnt_geteta_fmt(buf,
		   status->time_since_upload > status->time_since_download
			? status->time_since_download
			: status->time_since_upload);
		gtk_label_set_label(GTK_LABEL(mwt_info[5]), buf);
		snprintf(buf, b, "%d", status->priority);
		gtk_label_set_label(GTK_LABEL(mwt_info[6]), buf);
		g_list_free(selected);
	} else if (gtk_revealer_get_child_revealed(
			GTK_REVEALER(tstats_revealer)))
		gtk_revealer_set_reveal_child(GTK_REVEALER(tstats_revealer),
				FALSE);
	
	return TRUE;
}

static void trnt_pause_toggle(GtkButton *pause, gpointer data) {
	gt_torrent *gtp;
	torrent_status *status;

	if ((gtp = (gt_torrent *)data) == NULL) {
		Console.error("%s: Could not get torrent object.",
			      "trnt_pause_toggle");
		return;
	} else if (!lt_trnt_handle_is_valid(gtp->th)) {
		Console.error("%s: Invalid torrent handle.",
			      "trnt_pause_toggle");
		return;
	}

	status = lt_trnt_handle_get_status(gtp->th);
	if (status->paused)
		lt_trnt_handle_resume(gtp->th);
	else
		lt_trnt_handle_pause(gtp->th);
}

static void trnt_show_properties(GSimpleAction *action, GVariant *param,
	gpointer data) {
	gt_torrent *gtp;

	if ((gtp = (gt_torrent *)data) == NULL) {
		Console.debug("%s: properties dialog attempted for NULL"
			      " torrent", "trnt_show_properties");
		return;
	}
	gt_gui_show_torrent_properties(gtp);	
}

static void trnt_open_folder(GSimpleAction *action, GVariant *param,
	gpointer data) {
	static char buf[2048];
	gt_torrent *gtp;
	torrent_status *status;
	gchar *argv[4];

	if ((gtp = (gt_torrent *)data) == NULL) {
		Console.debug("%s: folder open attempted for NULL"
			      " torrent", "trnt_open_folder");
		return;
	}
	status = lt_trnt_handle_get_status(gtp->th);
	argv[0] = "/usr/bin/nautilus";	// TODO: make this cross-platform
	argv[1] = "-s";
	snprintf(buf, 2048, "%s/%s", status->save_path, status->name);
	argv[2] = buf;
	argv[3] = NULL;
	if (!g_spawn_async(NULL, argv, NULL, G_SPAWN_DEFAULT,
			  NULL, NULL, NULL, NULL))
		Console.error("Could not open %s!", status->save_path);
}

static int trnt_update(gt_alert *ga) {
	char buf[100], buf2[100], buf3[100];
	uint64_t eta = 0;
	trnt_widgets *widgets = (trnt_widgets *) ga->trnt->data;
	torrent_status *status;
	GtkWidget *pimage;

	status = lt_trnt_handle_get_status(ga->trnt->th);

	// update button
	if ((pimage = gtk_button_get_image(widgets->pause)) != NULL)
		gtk_image_set_from_icon_name(GTK_IMAGE(pimage),
			status->paused || status->is_finished ?
				"media-playback-start-symbolic" :
				"media-playback-pause-symbolic",
			GTK_ICON_SIZE_BUTTON);
	if (status->is_finished)
		gtk_widget_set_sensitive(GTK_WIDGET(widgets->pause), FALSE);
	gtk_widget_set_tooltip_text(GTK_WIDGET(widgets->pause),
			status->paused ? "Resume downloading" :
		  (status->is_finished ? NULL :
					 "Pause downloading"));

	eta = gt_trnt_geteta(status->download_payload_rate,
			     status->total_done, status->total_wanted);
	//Console.debug("Torrent alert is %s", alert_str[ga->type]);

	gtk_label_set_text(widgets->name, status->name);
	if (!status->is_finished) {
		gt_trnt_getfsize(status->total_done, buf);
		gt_trnt_getfsize(status->total_wanted, buf2);
		snprintf(buf3, 100, "%s of %s", buf, buf2);
		gtk_label_set_text(widgets->payload, buf3);
	} else if (status->is_seeding)
		gtk_label_set_text(widgets->payload, "Seeding...");
	else
		gtk_label_set_text(widgets->payload, "Done");

	gt_trnt_geteta_fmt(buf, eta);
	gtk_label_set_text(widgets->eta, buf);

	if (!status->is_finished || !status->is_seeding)
		gtk_progress_bar_set_fraction(widgets->progress,
			(double) status->total_done / status->total_wanted);
	else
		gtk_progress_bar_pulse(widgets->progress);
	return 1;
}

static void trnt_item_destroy(GtkButton *button, gpointer data) {
	gtk_widget_destroy(GTK_WIDGET(data));
}

static void trnt_destroy(gpointer gt) {
	gt_torrent *gtp = (gt_torrent *) gt;

	// presume that we have yet to remove this torrent
	gt_core_session_remove_torrent(gtp);
	free(gtp->data);
	gtp->data = NULL;
	gt_trnt_destroy(gtp);
}
