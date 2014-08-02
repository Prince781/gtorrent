// gTorrent
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "wrappers/libtorrent.h"
#include "console.h"
#include "core.h"
#include "torrent.h"

int download_callback(session_status *);
int download_test(char *path);

int main(int argc, char *argv[]) {
	if (argc == 1) {
		Console.error("Usage: %s [torrent file]", argv[0]);
		return 1;
	}
	char savepath[100], tstring[20], fstring[10];
	uint64_t time_left = 3789,	// 1hr, 3 min, 9 sec
		fsize = 4000;

	Console.debug("Testing logging");
	Console.debug("Starting core...");
	Console.debug("Testing if '%s' is a magnet link: %s", "magnet:dldl",
		gt_core_is_maglink("magnet:dldl") ? "yes" : "no");
	
	if (gt_core_get_savepath(savepath))
		Console.debug("Save path is '%s'", savepath);
	else Console.error("Could not find save path!");
	Console.error("Testing error message %d.", 1);
	// test
	// file_storage *fs = lt_create_file_storage();
	gt_trnt_gettime(time_left, tstring);
	gt_trnt_getfsize(fsize, fstring);
	
	Console.debug("time_left = %"PRIu64" (%s)", time_left, tstring);
	Console.debug("fsize = %"PRIu64" (%s)", fsize, fstring);
	gt_trnt_getrate(fsize, fstring);
	Console.debug("rate = %s", fstring);
	
	return download_test(argv[1]);
}

int download_test(char *file) {
	if (!file)
		return 1;
	char savepath[100];
	session *sess = lt_session_create();
	trnt_params *tp = lt_trnt_params_create();
	trnt_info *ti = lt_trnt_info_create(file);

	if (! gt_core_get_savepath(savepath)) {	// 'Downloads' folder
		Console.error("Could not find save path!");
		return 1;
	}

	lt_session_listen_on(sess, 6881, 6889);

	lt_trnt_params_set_savepath(tp, savepath);
	lt_trnt_params_set_info(tp, ti);

	lt_session_add_torrent(sess, tp);	// begin downloading
	gt_trnt_listen(sess, download_callback);	// wait
	Console.debug("Done! File is saved in %s", savepath);
	return 0;
}

int download_callback(session_status *sstat) {
	static char drate[100];
	
	gt_trnt_getrate(sstat->download_rate, drate);
	Console.debug("downloading at %s...", drate);
	return 1;
}
