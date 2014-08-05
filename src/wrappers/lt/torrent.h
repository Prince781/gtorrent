#ifndef LT_TORRENT_H
#define LT_TORRENT_H

#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

#define LT_STATUS_DIR_LEN	1024
#define LT_STATUS_LEN		100	// maximum status string length

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

struct torrent_handle;	// libtorrent::torrent_handle
typedef struct torrent_handle torrent_handle;

struct trnt_stat_tag {	// libtorrent::torrent_status
	// torrent_handle handle
	char			error[LT_STATUS_LEN];
	char			save_path[LT_STATUS_DIR_LEN];
	char			name[LT_STATUS_LEN];
	// intrusive_ptr<const torrent_info> torrent_file
	// boost::posix_time::time_duration next_announce
	// boost::posix_time::time_duration announce_interval
	char			current_tracker[LT_STATUS_LEN];
	uint64_t		total_download;
	uint64_t		total_upload;
	uint64_t		total_payload_download;
	uint64_t		total_payload_upload;
	uint64_t		total_redundant_bytes;
	// bitfield pieces
	// bitfield verified_pieces
	uint64_t		total_done;
	uint64_t		total_wanted_done;
	uint64_t		total_wanted;
	uint64_t		all_time_upload;
	uint64_t		all_time_download;
	time_t			added_time;
	time_t			completed_time;
	time_t			last_seen_complete;
	// storage_mode_t storage_mode
	float			progress;
	int			progress_ppm;
	int			queue_position;
	int			download_rate;
	int			upload_rate;
	int			download_payload_rate;
	int			num_seeds;
	int			num_peers;
	int			num_complete;
	int			num_incomplete;
	int			list_seeds;
	int			connect_candidates;
	int			num_pieces;
	int			distributed_full_copies;
	int			distributed_fraction;
	float			distributed_copies;
	int			block_size;
	int			num_uploads;
	int			num_connections;
	int			uploads_limit;
	int			connections_limit;
	int			up_bandwidth_queue;
	int			down_bandwidth_queue;
	int			time_since_upload;
	int			time_since_download;
	int			active_time;
	int			finished_time;
	int			seeding_time;
	int			seed_rank;
	int			last_scrape;
	int			sparse_regions;
	int			priority;
	enum torrent_state 	state;
	bool			need_save_resume;
	bool			ip_filter_applies;
	bool			upload_mode;
	bool			share_mode;
	bool			super_seeding;
	bool			paused;
	bool			auto_managed;
	bool			sequential_download;
	bool			is_seeding;
	bool			is_finished;
	bool			has_metadata;
	bool			seed_mode;
	bool			moving_storage;
	// sha1_hash info_hash
};
typedef struct trnt_stat_tag torrent_status;

struct torrent_vector;	// std::vector<libtorrent::torrent_handle>
typedef struct torrent_vector torrent_vector;

/* @lt_trnt_params_create(): create a new torrent_params */
torrent_params	*lt_trnt_params_create		(void);

/* @lt_trnt_params_destroy(): destroy torrent_params */
void		lt_trnt_params_destroy		(torrent_params *tp);

/* @lt_trnt_params_set_savepath(): set savepath when torrent is finished */
void		lt_trnt_params_set_savepath	(torrent_params *tp,
						 const char *path);

/* @lt_trnt_info_create(): create torrent info from torrent file location */
torrent_info	*lt_trnt_info_create		(const char *path);

/* @lt_trnt_info_destroy(): destroy torrent info */
void		lt_trnt_info_destroy		(torrent_info *ti);

/* @lt_trnt_params_set_info(): set torrent info of torrent_params */
void		lt_trnt_params_set_info	(torrent_params *tp, torrent_info *ti);

/* @lt_trnt_params_get_name(): get name of torrent params */
const char	*lt_trnt_params_get_name	(torrent_params *tp);

/* @lt_trnt_handle_is_valid(): determine if torrent handle is valid */
bool		lt_trnt_handle_is_valid		(torrent_handle *th);

/* @lt_trnt_handle_destroy(): destroys a torrent_handle that was allocated
 * by a call to lt_session_add_torrent() */
void		lt_trnt_handle_destroy		(torrent_handle *th);

/* @lt_trnt_handle_get_status(): get status from torrent handle */
torrent_status	*lt_trnt_handle_get_status	(torrent_handle *th);

/* @lt_trnt_vector_get(): get a torrent handle from a torrent vector */
torrent_handle	*lt_trnt_vector_get	(torrent_vector *tv, uint64_t i);

/* @lt_trnt_handle_equal(): test for equality between torrent handles */
bool		lt_trnt_handle_equal	(torrent_handle *a, torrent_handle *b);

#endif
