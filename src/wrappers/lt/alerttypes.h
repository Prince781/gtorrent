#ifndef LT_ALERTTYPES_H
#define LT_ALERTTYPES_H

#include <inttypes.h>
#include "torrent.h"

struct alert;		// libtorrent::alert
typedef struct alert alert;

#define __ATYPE(f) \
	f(torrent_alert) \
	f(peer_alert) \
	f(tracker_alert) \
	f(torrent_added_alert) \
	f(torrent_removed_alert) \
	f(read_piece_alert) \
	f(file_completed_alert) \
	f(file_renamed_alert) \
	f(file_rename_failed_alert) \
	f(performance_alert) \
	f(state_changed_alert) \
	f(tracker_error_alert) \
	f(tracker_warning_alert) \
	f(scrape_reply_alert) \
	f(scrape_failed_alert) \
	f(tracker_reply_alert) \
	f(dht_reply_alert) \
	f(tracker_announce_alert) \
	f(hash_failed_alert) \
	f(peer_ban_alert) \
	f(peer_unsnubbed_alert) \
	f(peer_snubbed_alert) \
	f(peer_error_alert) \
	f(peer_connect_alert) \
	f(peer_disconnected_alert) \
	f(invalid_request_alert) \
	f(torrent_finished_alert) \
	f(piece_finished_alert) \
	f(request_dropped_alert) \
	f(block_timeout_alert) \
	f(block_finished_alert) \
	f(block_downloading_alert) \
	f(unwanted_block_alert) \
	f(storage_moved_alert) \
	f(storage_moved_failed_alert) \
	f(torrent_deleted_alert) \
	f(torrent_delete_failed_alert) \
	f(save_resume_data_alert) \
	f(save_resume_data_failed_alert) \
	f(torrent_paused_alert) \
	f(torrent_resumed_alert) \
	f(torrent_checked_alert) \
	f(url_seed_alert) \
	f(file_error_alert) \
	f(metadata_failed_alert) \
	f(metadata_received_alert) \
	f(udp_error_alert) \
	f(external_ip_alert) \
	f(listen_failed_alert) \
	f(listen_succeeded_alert) \
	f(portmap_error_alert) \
	f(portmap_alert) \
	f(portmap_log_alert) \
	f(fastresume_rejected_alert) \
	f(peer_blocked_alert) \
	f(dht_announce_alert) \
	f(dht_get_peers_alert) \
	f(stats_alert) \
	f(cache_flushed_alert) \
	f(anonymous_mode_alert) \
	f(lsd_peer_alert) \
	f(trackerid_alert) \
	f(dht_bootstrap_alert) \
	f(rss_alert) \
	f(torrent_error_alert) \
	f(torrent_need_cert_alert) \
	f(incoming_connection_alert) \
	f(add_torrent_alert) \
	f(state_update_alert) \
	f(torrent_update_alert) \
	f(rss_item_alert) \
	f(dht_error_alert) \
	f(dht_immutable_item_alert) \
	f(dht_mutable_item_alert) \
	f(dht_put_alert) \
	f(i2p_alert) \
	f(other_alert)

#define __ALENUM(x) x,
#define __ALSARR(x) #x,

enum alert_type { __ATYPE(__ALENUM) };
extern const char *alert_str[];

enum alert_category {
	error_notification		= 0x00000001,
	peer_notification		= 0x00000002,
	port_mapping_notification	= 0x00000004,
	storage_notification		= 0x00000008,
	tracker_notification		= 0x00000010,
	debug_notification		= 0x00000020,
	status_notification		= 0x00000040,
	progress_notification		= 0x00000080,
	ip_block_notification		= 0x00000100,
	performance_warning		= 0x00000200,
	dht_notification		= 0x00000400,
	stats_notification		= 0x00000800,
	rss_notification		= 0x00001000,
	all_categories			= 0x7FFFFFFF
};

struct alert_deque;	// std::deque<libtorrent::alert*>
typedef struct alert_deque alert_deque;

/* @lt_alert_get_type(): get the alert type */
enum alert_type	lt_alert_get_type		(alert *a);

/* @lt_alert_get_torrent_handle(): get the torrent handle of an alert, if it
 * is a torrent_alert. Note that explicit checking must be done before calling
 * this function. */
torrent_handle	*lt_alert_get_torrent_handle	(alert *a);

/* @lt_alert_deque_create(): create an alert deque */
alert_deque	*lt_alert_deque_create		(void);

/* @lt_alert_deque_destroy(): destroy an alert deque */
void		lt_alert_deque_destroy		(alert_deque *ad);

/* @lt_alert_deque_size(): get alert deque size */
uint64_t	lt_alert_deque_size		(alert_deque *ad);

/* @lt_alert_deque_get(): get alert at position in alert_deque */
alert		*lt_alert_deque_get		(alert_deque *ad, uint64_t i);

#endif
