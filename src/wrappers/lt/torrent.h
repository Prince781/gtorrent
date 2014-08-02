#ifndef LT_TORRENT_H
#define LT_TORRENT_H

#include <inttypes.h>
#include <stdbool.h>

struct torrent_params;	// libtorrent::add_torrent_params
typedef struct torrent_params torrent_params;

struct torrent_info;	// libtorrent::torrent_info
typedef struct torrent_info torrent_info;

enum torrent_state {	// libtorrent::torrent_status::state_t
	queued_for_checking,
	checking_files,
	downloading_metadata,
	downloading,
	finished,
	seeding,
	allocating,
	checking_resume_data,
	unknown
};

struct trnt_stat_tag {	// libtorrent::torrent_status
	// trnt_handle	*handle;
	enum torrent_state	state;
	bool			paused;
	bool			auto_managed;
	bool			sequential_download;
	bool			is_seeding;
	bool			is_finished;
	float			progress;
	int			progress_ppm;
	const char		*error;
	// boost::posix_time::time_duration next_announce
	// boost::posix_time::time_duration announce_interval
	const char		*current_tracker;
	uint64_t		total_download;
	uint64_t		total_upload;
	uint64_t		total_payload_download;
	uint64_t		total_payload_upload;
	uint64_t		total_failed_bytes;
	uint64_t		total_redundant_bytes;
	int			download_rate;
	int			upload_rate;
	int			download_payload_rate;
	int			upload_payload_rate;
	int			num_peers;
	int			num_complete;
	int			num_incomplete;
	int			list_seeds;
	int			list_peers;
	int			connect_candidates;
	// bitfield pieces
	// bitfield verified_pieces
	int			num_pieces;
	uint64_t		total_done;
	uint64_t		total_wanted_done;
	uint64_t		total_wanted;
	int			num_seeds;
	int			distributed_full_copies;
	int			distributed_fraction;
	float			distributed_copies;
	int			block_size;
	int			num_uploads;
	int			num_connections;
	int			uploads_limit;
	int			connections_limit;
	// storage_mode_t storage_mode
	int			up_bandwidth_queue;
	int			down_bandwidth_queue;
	uint64_t		all_time_upload;
	uint64_t		all_time_download;
	int			active_time;
	int			finished_time;
	int			seeding_time;
	int			seed_rank;
	int			last_scrape;
	bool			has_incoming;
	int			sparse_regions;
	bool			seed_mode;
	bool			upload_mode;
	bool			share_mode;
	bool			super_seeding;
	int			priority;
	time_t			*added_time;
	time_t			*completed_time;
	time_t			*last_seen_complete;
	int			time_since_upload;
	int			time_since_download;
	int			queue_position;
	bool			need_save_resume;
	bool			ip_filter_applies;
	// sha1_hash info_hash
	int			listen_port;
};
typedef struct trnt_stat_tag torrent_status;

struct torrent_handle;	// libtorrent::torrent_handle
typedef struct torrent_handle torrent_handle;

/* @lt_trnt_params_create(): create a new trnt_params */
torrent_params	*lt_trnt_params_create		(void);

/* @lt_trnt_params_set_savepath(): set savepath when torrent is finished */
void		lt_trnt_params_set_savepath	(torrent_params *tp,
						 const char *path);

/* @lt_trnt_info_create(): create torrent info from torrent file location */
torrent_info	*lt_trnt_info_create		(const char *path);

/* @lt_trnt_params_set_info(): set torrent info of torrent_params */
void		lt_trnt_params_set_info	(torrent_params *tp, torrent_info *ti);

/* @lt_trnt_handle_is_valid(): determine if torrent handle is valid */
bool		lt_trnt_handle_is_valid		(torrent_handle *th);

/* @lt_trnt_handle_get_status(): get status from torrent handle */
torrent_status	*lt_trnt_handle_get_status	(torrent_handle *th);

#endif
