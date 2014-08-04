#include "deps.hpp"

extern "C" {

#include "alerttypes.h"

#define LTA(_name_)		libtorrent::_name_::alert_type
#define LTA_TYPE(_name_)	(enum alert_type) (_name_)

const char *alert_str[] = { __ATYPE(__ALSARR) };

enum alert_type lt_alert_get_type(alert *a) {
	switch (reinterpret_cast<libtorrent::alert*>(a)->type()) {
		case LTA(torrent_alert):
			return LTA_TYPE(torrent_alert);
		case LTA(peer_alert):
			return LTA_TYPE(peer_alert);
		case LTA(tracker_alert):
			return LTA_TYPE(tracker_alert);
		case LTA(torrent_added_alert):
			return LTA_TYPE(torrent_added_alert);
		case LTA(torrent_removed_alert):
			return LTA_TYPE(torrent_removed_alert);
		case LTA(read_piece_alert):
			return LTA_TYPE(read_piece_alert);
		case LTA(file_completed_alert):
			return LTA_TYPE(file_completed_alert);
		case LTA(file_renamed_alert):
			return LTA_TYPE(file_renamed_alert);
		case LTA(file_rename_failed_alert):
			return LTA_TYPE(file_rename_failed_alert);
		case LTA(performance_alert):
			return LTA_TYPE(performance_alert);
		case LTA(state_changed_alert):
			return LTA_TYPE(state_changed_alert);
		case LTA(tracker_error_alert):
			return LTA_TYPE(tracker_error_alert);
		case LTA(tracker_warning_alert):
			return LTA_TYPE(tracker_warning_alert);
		case LTA(scrape_reply_alert):
			return LTA_TYPE(scrape_reply_alert);
		case LTA(scrape_failed_alert):
			return LTA_TYPE(scrape_failed_alert);
		case LTA(tracker_reply_alert):
			return LTA_TYPE(tracker_reply_alert);
		case LTA(dht_reply_alert):
			return LTA_TYPE(dht_reply_alert);
		case LTA(tracker_announce_alert):
			return LTA_TYPE(tracker_announce_alert);
		case LTA(hash_failed_alert):
			return LTA_TYPE(hash_failed_alert);
		case LTA(peer_ban_alert):
			return LTA_TYPE(peer_ban_alert);
		case LTA(peer_unsnubbed_alert):
			return LTA_TYPE(peer_unsnubbed_alert);
		case LTA(peer_snubbed_alert):
			return LTA_TYPE(peer_snubbed_alert);
		case LTA(peer_error_alert):
			return LTA_TYPE(peer_error_alert);
		case LTA(peer_connect_alert):
			return LTA_TYPE(peer_connect_alert);
		case LTA(peer_disconnected_alert):
			return LTA_TYPE(peer_disconnected_alert);
		case LTA(invalid_request_alert):
			return LTA_TYPE(invalid_request_alert);
		case LTA(torrent_finished_alert):
			return LTA_TYPE(torrent_finished_alert);
		case LTA(piece_finished_alert):
			return LTA_TYPE(piece_finished_alert);
		case LTA(request_dropped_alert):
			return LTA_TYPE(request_dropped_alert);
		case LTA(block_timeout_alert):
			return LTA_TYPE(block_timeout_alert);
		case LTA(block_finished_alert):
			return LTA_TYPE(block_finished_alert);
		case LTA(block_downloading_alert):
			return LTA_TYPE(block_downloading_alert);
		case LTA(unwanted_block_alert):
			return LTA_TYPE(unwanted_block_alert);
		case LTA(storage_moved_alert):
			return LTA_TYPE(storage_moved_alert);
		case LTA(storage_moved_failed_alert):
			return LTA_TYPE(storage_moved_failed_alert);
		case LTA(torrent_deleted_alert):
			return LTA_TYPE(torrent_deleted_alert);
		case LTA(torrent_delete_failed_alert):
			return LTA_TYPE(torrent_delete_failed_alert);
		case LTA(save_resume_data_alert):
			return LTA_TYPE(save_resume_data_alert);
		case LTA(save_resume_data_failed_alert):
			return LTA_TYPE(save_resume_data_failed_alert);
		case LTA(torrent_paused_alert):
			return LTA_TYPE(torrent_paused_alert);
		case LTA(torrent_resumed_alert):
			return LTA_TYPE(torrent_resumed_alert);
		case LTA(torrent_checked_alert):
			return LTA_TYPE(torrent_checked_alert);
		case LTA(url_seed_alert):
			return LTA_TYPE(url_seed_alert);
		case LTA(file_error_alert):
			return LTA_TYPE(file_error_alert);
		case LTA(metadata_failed_alert):
			return LTA_TYPE(metadata_failed_alert);
		case LTA(metadata_received_alert):
			return LTA_TYPE(metadata_received_alert);
		case LTA(udp_error_alert):
			return LTA_TYPE(udp_error_alert);
		case LTA(external_ip_alert):
			return LTA_TYPE(external_ip_alert);
		case LTA(listen_failed_alert):
			return LTA_TYPE(listen_failed_alert);
		case LTA(listen_succeeded_alert):
			return LTA_TYPE(listen_succeeded_alert);
		case LTA(portmap_error_alert):
			return LTA_TYPE(portmap_error_alert);
		case LTA(portmap_alert):
			return LTA_TYPE(portmap_alert);
		case LTA(portmap_log_alert):
			return LTA_TYPE(portmap_log_alert);
		case LTA(fastresume_rejected_alert):
			return LTA_TYPE(fastresume_rejected_alert);
		case LTA(peer_blocked_alert):
			return LTA_TYPE(peer_blocked_alert);
		case LTA(dht_announce_alert):
			return LTA_TYPE(dht_announce_alert);
		case LTA(dht_get_peers_alert):
			return LTA_TYPE(dht_get_peers_alert);
		case LTA(stats_alert):
			return LTA_TYPE(stats_alert);
		case LTA(cache_flushed_alert):
			return LTA_TYPE(cache_flushed_alert);
		case LTA(anonymous_mode_alert):
			return LTA_TYPE(anonymous_mode_alert);
		case LTA(lsd_peer_alert):
			return LTA_TYPE(lsd_peer_alert);
		case LTA(trackerid_alert):
			return LTA_TYPE(trackerid_alert);
		case LTA(dht_bootstrap_alert):
			return LTA_TYPE(dht_bootstrap_alert);
		case LTA(rss_alert):
			return LTA_TYPE(rss_alert);
		case LTA(torrent_error_alert):
			return LTA_TYPE(torrent_error_alert);
		case LTA(torrent_need_cert_alert):
			return LTA_TYPE(torrent_need_cert_alert);
		case LTA(incoming_connection_alert):
			return LTA_TYPE(incoming_connection_alert);
		case LTA(add_torrent_alert):
			return LTA_TYPE(add_torrent_alert);
		case LTA(state_update_alert):
			return LTA_TYPE(state_update_alert);
		case LTA(torrent_update_alert):
			return LTA_TYPE(torrent_update_alert);
		case LTA(rss_item_alert):
			return LTA_TYPE(rss_item_alert);
		case LTA(dht_error_alert):
			return LTA_TYPE(dht_error_alert);
		case LTA(dht_immutable_item_alert):
			return LTA_TYPE(dht_immutable_item_alert);
		case LTA(dht_mutable_item_alert):
			return LTA_TYPE(dht_mutable_item_alert);
		case LTA(dht_put_alert):
			return LTA_TYPE(dht_put_alert);
		case LTA(i2p_alert):
			return LTA_TYPE(i2p_alert);
		default:
			return LTA_TYPE(other_alert);
	}
}

torrent_handle *lt_alert_get_torrent_handle(alert *a) {
	libtorrent::torrent_handle *th
		= &reinterpret_cast<libtorrent::torrent_alert*>(a)->handle;
	return reinterpret_cast<torrent_handle*>(th);
}

alert_deque *lt_alert_deque_create(void) {
	return reinterpret_cast<alert_deque*>
		(new std::deque<libtorrent::alert*>());
}

void lt_alert_deque_destroy(alert_deque *ad) {
	delete reinterpret_cast<std::deque<libtorrent::alert*>*>(ad);
}

uint64_t lt_alert_deque_size(alert_deque *ad) {
	return (uint64_t)
		reinterpret_cast<std::deque<libtorrent::alert*>*>(ad)->size();
}

alert *lt_alert_deque_get(alert_deque *ad, uint64_t i) {
	std::deque<libtorrent::alert*> *dq
		= reinterpret_cast<std::deque<libtorrent::alert*>*>(ad);

	if (i < dq->size())
		return reinterpret_cast<alert*>(dq->at(i));
	else return NULL;
}

}
