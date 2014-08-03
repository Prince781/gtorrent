// gTorrent
#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "test.h"
#include "gui/main_window.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Usage: %s [torrent file]\n", argv[0]);
		return 1;
	}

	Console.debug("Testing logging");
	Console.debug("Starting core...");
	
	Console.error("Testing error message %d.", 1);

	// test_download(argv[1]);
	gt_gui_main_window_init(argc, argv);
	
	return 0;
}
