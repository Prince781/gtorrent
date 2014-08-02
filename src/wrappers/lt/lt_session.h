#ifndef LT_SESSION_H
#define LT_SESSION_H

#include <inttypes.h>
#include <stdbool.h>
#include "lt_torrent.h"

struct session;		// libtorrent::session
typedef struct session session;

/**
 * This is necessary since libtorrent::session::status() returns a snapshot
 * of current session status (libtorrent::session_status), which is not ideal
 * since local variables pointing to this will do so to temporary memory. We
 * cannot reinterpret_cast this to one of our "fake" structs here either.
 */
struct sess_stat_tag {	// libtorrent::session_status
	bool		has_incoming_connections;
	int		upload_rate;
	int		download_rate;
	uint64_t	total_download;
	uint64_t	total_upload;
	int		payload_upload_rate;
	int		payload_download_rate;
	uint64_t	total_payload_download;
	uint64_t	total_payload_upload;
	int		ip_overhead_upload_rate;
	int		ip_overhead_download_rate;
	uint64_t	total_ip_overhead_download;
	uint64_t	total_ip_overhead_upload;
	int		dht_upload_rate;
	int		dht_download_rate;
	uint64_t	total_dht_download;
	uint64_t	total_dht_upload;
	int		tracker_upload_rate;
	int		tracker_download_rate;
	uint64_t	total_tracker_download;
	uint64_t	total_tracker_upload;
	uint64_t	total_redundant_bytes;
	uint64_t	total_failed_bytes;
	int		num_peers;
	int		num_unchoked;
	int		allowed_upload_slots;
	int		up_bandwidth_queue;
	int		down_bandwidth_queue;
	int		optimistic_unchoke_counter;
	int		unchoke_counter;
	int		disk_write_queue;
	int		disk_read_queue;
	int		dht_nodes;
	int		dht_node_cache;
	int		dht_torrents;
	uint64_t	dht_global_nodes;
	// std::vector<dht_lookup> active_requests
	// std::vector<dht_routing_bucket> dht_routing_table
	int		dht_total_allocations;
	// utp_status utp_stats
	int		peerlist_size;
};
typedef struct sess_stat_tag session_status;

/* @lt_session_create(): create a new session */
session		*lt_session_create		(void);

/* @lt_session_pause(): pause a session */
void 		lt_session_pause		(session *s);

/* @lt_session_resumse(): resume a paused session */
void		lt_session_resume		(session *s);

/* @lt_session_is_paused(): check if session is paused */
bool		lt_session_is_paused		(session *s);

/* @lt_session_listen_on(): set port range for listening */
void		lt_session_listen_on		(session *s, int x, int y);

/* @lt_session_is_listening(): check if session has successfully opened a
 * listening port */
bool		lt_session_is_listening		(session *s);

/* @lt_session_add_torrent(): add a torrent to a session */
void		lt_session_add_torrent		(session *s, trnt_params *tp);

/* @lt_session_get_status(): get session status */
void		lt_session_get_status	(session *s, session_status *ss);

/* @lt_session_status_create(): create new session status */
session_status *lt_session_status_create	(void);

#endif
