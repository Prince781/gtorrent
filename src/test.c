// test gtorrent functionality thus far
#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "core.h"
#include "torrent.h"
#include "alerts.h"
#include "wrappers/libtorrent.h"

/* @download_callback(): callback function for session */
// static int session_callback(gt_alert *);
static int torrent_callback(gt_alert *);

int main(int argc, char *argv[]) {
	gt_torrent *gtor;
	char save_path[1024];
	torrent_status *status;

	if (argc == 1) {
		printf("Usage: %s [torrent file]\n", argv[0]);
		return 1;
	}

	Console.debug("Initializing core...");

	gt_core_session_start(GT_CORE_DEFAULT_PORTS());
	
	if (!gt_core_get_savepath(save_path)) {
		Console.error("Could not get save path.");
		gt_core_session_end();
		return 1;
	}

	if ((gtor = gt_trnt_create(argv[1], save_path)) == NULL) {
		Console.error("Could not create torrent.");
		gt_core_session_end();
		return 1;
	}

//	gt_core_session_set_callback(session_callback);
	gtor->call = torrent_callback;

	if (!gt_core_session_add_torrent(gtor)) {
		Console.error("Could not add torrent.");
		gt_core_session_end();
		return 1;
	}

	do {
		gt_core_session_update();
		status = lt_trnt_handle_get_status(gtor->th);
	} while (!status->is_finished);

	Console.debug("Download complete.");

	Console.debug("gTorrent terminating...");
	gt_core_session_end();

	return 0;
}


// respond to status updates
static int session_callback(gt_alert *ga) {
	//char buf[100];
	//session_status *ss = lt_session_get_status(ga->ses);

	// gt_trnt_getrate(ss->payload_download_rate, buf);
	Console.debug("Session alert is %s", alert_str[ga->type]);
	// Console.debug("Download rate (payload): %s", buf);
	return 1;
}

// respond to torrent updates
static int torrent_callback(gt_alert *ga) {
	char buf[100];
	torrent_status *status;

	status = lt_trnt_handle_get_status(ga->trnt->th);
	gt_trnt_getrate(status->download_payload_rate, buf);
	Console.debug("Torrent alert is %s", alert_str[ga->type]);
	Console.debug("DL rate: %s", buf);
	return 1;
}
