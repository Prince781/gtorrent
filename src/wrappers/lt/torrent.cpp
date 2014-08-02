#include "deps.hpp"

extern "C" {

#include <stdio.h>
#include "torrent.h"

/* @lt_trnt_status_cnvt(): convert a torrent status */
static void lt_trnt_status_cnvt(libtorrent::torrent_handle *, torrent_status *);

/* @lt_trnt_state_cnvt(): convert a torrent state */
static enum torrent_state
	lt_trnt_state_cnvt(enum libtorrent::torrent_status::state_t);

torrent_params *lt_trnt_params_create(void) {
	return reinterpret_cast<torrent_params*>
		(new libtorrent::add_torrent_params());
}

void lt_trnt_params_set_savepath(torrent_params *tp, const char *path) {
	libtorrent::add_torrent_params *torp
		= reinterpret_cast<libtorrent::add_torrent_params*>(tp);
	torp->save_path = std::string(path);
}

torrent_info *lt_trnt_info_create(const char *path) {
	return reinterpret_cast<torrent_info*>
		(new libtorrent::torrent_info(std::string(path)));
}

void lt_trnt_params_set_info(torrent_params *tp, torrent_info *ti) {
	libtorrent::add_torrent_params *torp
		= reinterpret_cast<libtorrent::add_torrent_params*>(tp);
	torp->ti = reinterpret_cast<libtorrent::torrent_info*>(ti);
}

bool lt_trnt_handle_is_valid(torrent_handle *th) {
	return reinterpret_cast<libtorrent::torrent_handle*>(th)->is_valid();
}

torrent_status *lt_trnt_handle_get_status(torrent_handle *th) {
	static torrent_status ts;

	lt_trnt_status_cnvt(reinterpret_cast<libtorrent::torrent_handle*>(th),
			    &ts);
	return &ts;
}

static void lt_trnt_status_cnvt(libtorrent::torrent_handle *th,
	torrent_status *ts) {
	th->is_valid();
	libtorrent::torrent_status tstat = th->status();
	ts->state = lt_trnt_state_cnvt(tstat.state);
	ts->paused = tstat.paused;
	ts->auto_managed = tstat.auto_managed;
	ts->sequential_download = tstat.sequential_download;
	ts->is_seeding = tstat.is_seeding;
	ts->is_finished = tstat.is_finished;
	ts->progress = tstat.progress;
	ts->progress_ppm = tstat.progress_ppm;
	ts->error = tstat.error.c_str();	// may be unsafe
	ts->current_tracker = tstat.current_tracker.c_str();
	ts->total_download = tstat.total_download;
	ts->total_upload = tstat.total_upload;
	ts->total_payload_download = tstat.total_payload_download;
	ts->total_payload_upload = tstat.total_payload_upload;
	ts->total_failed_bytes = tstat.total_failed_bytes;
	ts->total_redundant_bytes = tstat.total_redundant_bytes;
	ts->download_rate = tstat.download_rate;
	ts->upload_rate = tstat.upload_rate;
	ts->download_payload_rate = tstat.download_payload_rate;
	ts->upload_payload_rate = tstat.upload_payload_rate;
	ts->num_peers = tstat.num_peers;
	ts->num_complete = tstat.num_complete;
	ts->list_seeds = tstat.list_seeds;
	ts->list_peers = tstat.list_peers;
	ts->connect_candidates = tstat.connect_candidates;
	// TODO: bitfield pieces
	// TODO: bitfield verified_pieces
	ts->num_pieces = tstat.num_pieces;
	ts->total_done = tstat.total_done;
	ts->total_wanted_done = tstat.total_wanted_done;
	ts->total_wanted = tstat.total_wanted;
	ts->num_seeds = tstat.num_seeds;
	ts->distributed_full_copies = tstat.distributed_full_copies;
	ts->distributed_fraction = tstat.distributed_fraction;
	ts->distributed_copies = tstat.distributed_copies;
	ts->block_size = tstat.block_size;
	ts->num_uploads = tstat.num_uploads;
	ts->num_connections = tstat.num_connections;
	ts->uploads_limit = tstat.uploads_limit;
	ts->connections_limit = tstat.connections_limit;
	// TODO: storage_mode_t storage_mode
	ts->up_bandwidth_queue = tstat.up_bandwidth_queue;
	ts->down_bandwidth_queue = tstat.down_bandwidth_queue;
	ts->all_time_upload = tstat.all_time_upload;
	ts->all_time_download = tstat.all_time_download;
	ts->active_time = tstat.active_time;
	ts->finished_time = tstat.finished_time;
	ts->seeding_time = tstat.seeding_time;
	ts->seed_rank = tstat.seed_rank;
	ts->last_scrape = tstat.last_scrape;
	ts->has_incoming = tstat.has_incoming;
	ts->sparse_regions = tstat.sparse_regions;
	ts->seed_mode = tstat.seed_mode;
	ts->upload_mode = tstat.upload_mode;
	ts->share_mode = tstat.share_mode;
	ts->super_seeding = tstat.super_seeding;
	ts->priority = tstat.priority;
	ts->added_time = &tstat.added_time;
	ts->completed_time = &tstat.completed_time;
	ts->last_seen_complete = &tstat.last_seen_complete;
	ts->time_since_upload = tstat.time_since_upload;
	ts->time_since_download = tstat.time_since_download;
	ts->queue_position = tstat.queue_position;
	ts->need_save_resume = tstat.need_save_resume;
	ts->ip_filter_applies = tstat.ip_filter_applies;
	// TODO: sha1_hash info_hash
	ts->listen_port = tstat.listen_port;
}

static enum torrent_state
	lt_trnt_state_cnvt(enum libtorrent::torrent_status::state_t state) {
	switch (state) {
	case queued_for_checking:
		return (enum torrent_state) queued_for_checking;
	case checking_files:
		return (enum torrent_state) checking_files;
	case downloading_metadata:
		return (enum torrent_state) downloading_metadata;
	case downloading:
		return (enum torrent_state) downloading;
	case finished:
		return (enum torrent_state) finished;
	case seeding:
		return (enum torrent_state) seeding;
	case allocating:
		return (enum torrent_state) allocating;
	case checking_resume_data:
		return (enum torrent_state) checking_resume_data;
	default:
		return (enum torrent_state) unknown;
	}
}

}
