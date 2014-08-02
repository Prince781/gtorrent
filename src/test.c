// test gtorrent functionality thus far
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "console.h"
#include "core.h"
#include "wrappers/libtorrent.h"

static torrent_handle *handles[MAX_TORRENTS];

static int download_callback(session *ses);

void test_download(const char *file_path) {
	char save_path[1024];
	session *ses = lt_session_create();
	torrent_params *tp = lt_trnt_params_create();
	torrent_info *ti = lt_trnt_info_create(file_path);

	if (!ti) {
		Console.error("Invalid file path.");
		return;
	} else if (!gt_core_get_savepath(save_path)) {
		Console.error("Could not get save path.");
		return;
	}

	Console.debug("Saving to %s...", save_path);

	lt_session_listen_on(ses, LISTEN_PORT_X, LISTEN_PORT_Y);
	lt_trnt_params_set_savepath(tp, save_path);
	lt_trnt_params_set_info(tp, ti);
	lt_session_add_torrent(ses, tp);	// start torrent download

	Console.debug("Starting callback handler...");
	gt_trnt_listen(ses, download_callback);	// attach callback handler
}

// query and respond to status updates
static int download_callback(session *ses) {
	char dlspeed[20];
	session_status *sstat = lt_session_get_status(ses);
	torrent_handle **th = handles;
	torrent_status *ts;

	lt_session_get_torrents(ses, handles);	// fill handles
	for (; *th != NULL; ++th) {
		if (!lt_trnt_handle_is_valid(*th)) {
			Console.error("Torrent handle is invalid!");
			continue;
		}
		ts = lt_trnt_handle_get_status(*th);
		gt_trnt_getrate(ts->download_rate, dlspeed);
		Console.debug("Downloading at %s", dlspeed);
	}

	return 1;	// TODO: check against status
}
