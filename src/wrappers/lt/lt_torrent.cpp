#include "lt_deps.hpp"

extern "C" {

#include "lt_torrent.h"

trnt_params *lt_trnt_params_create(void) {
	return reinterpret_cast<trnt_params*>
		(new libtorrent::add_torrent_params());
}

void lt_trnt_params_set_savepath(trnt_params *tp, char *path) {
	libtorrent::add_torrent_params *torp
		= reinterpret_cast<libtorrent::add_torrent_params*>(tp);
	torp->save_path = std::string(path);
}

trnt_info *lt_trnt_info_create(char *path) {
	return reinterpret_cast<trnt_info*>
		(new libtorrent::torrent_info(std::string(path)));
}

void lt_trnt_params_set_info(trnt_params *tp, trnt_info *ti) {
	libtorrent::add_torrent_params *torp
		= reinterpret_cast<libtorrent::add_torrent_params*>(tp);
	torp->ti = reinterpret_cast<libtorrent::torrent_info*>(ti);
}

}
