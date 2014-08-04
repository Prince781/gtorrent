// initialize gTorrent and GTK+
#include "../core.h"
#include "main_window.h"

int main(int argc, char *argv[]) {
	return gt_core_init(argc, argv, gt_gui_main_window_init);
}
