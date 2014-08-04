#include "deps.hpp"

extern "C" {

#include <stdlib.h>
#include "session.h"

/* @lt_sstat_cnvt: convert a session status */
static void lt_sstat_cnvt(libtorrent::session_status, session_status *);

session* lt_session_create(void) {
	return reinterpret_cast<session*>(new libtorrent::session());
}

void lt_session_destroy(session *s) {
	delete reinterpret_cast<libtorrent::session*>(s);
}

void lt_session_pause(session *s) {
	reinterpret_cast<libtorrent::session*>(s)->pause();
}

void lt_session_resume(session *s) {
	reinterpret_cast<libtorrent::session*>(s)->resume();
}

bool lt_session_is_paused(session *s) {
	return reinterpret_cast<libtorrent::session*>(s)->is_paused();
}

void lt_session_listen_on(session *s, int x, int y) {
	libtorrent::session *ses = reinterpret_cast<libtorrent::session*>(s);
	ses->listen_on(std::make_pair(x, y));
}

bool lt_session_is_listening(session *s) {
	return reinterpret_cast<libtorrent::session*>(s)->is_listening();
}

torrent_handle *lt_session_add_torrent(session *s, torrent_params *tp) {
	libtorrent::session *ses = reinterpret_cast<libtorrent::session*>(s);
	libtorrent::add_torrent_params *torp
		= reinterpret_cast<libtorrent::add_torrent_params*>(tp);
	libtorrent::torrent_handle *th = new libtorrent::torrent_handle();
	*th = ses->add_torrent(*torp);
	return reinterpret_cast<torrent_handle*>(th);
}

void lt_session_remove_torrent(session *s, torrent_handle *th) {
	libtorrent::session *ses;
	libtorrent::torrent_handle *torh;

	ses = reinterpret_cast<libtorrent::session*>(s);
	torh = reinterpret_cast<libtorrent::torrent_handle*>(th);

	ses->remove_torrent(*torh);
	
}

session_status *lt_session_get_status(session *s) {
	static session_status ss;

	libtorrent::session *ses = reinterpret_cast<libtorrent::session*>(s);
	lt_sstat_cnvt(ses->status(), &ss);
	return &ss;
}

static void lt_sstat_cnvt(libtorrent::session_status sstat,
	session_status *ss) {
	ss->has_incoming_connections = sstat.has_incoming_connections;
	ss->upload_rate = sstat.upload_rate;
	ss->download_rate = sstat.download_rate;
	ss->total_download = (uint64_t) sstat.total_download;
	ss->total_upload = (uint64_t) sstat.total_upload;
	ss->payload_upload_rate = sstat.payload_upload_rate;
	ss->payload_download_rate = sstat.payload_download_rate;
	ss->total_payload_download = (uint64_t) sstat.total_payload_download;
	ss->total_payload_upload = (uint64_t) sstat.total_payload_upload;
	ss->ip_overhead_upload_rate = sstat.ip_overhead_upload_rate;
	ss->ip_overhead_download_rate = sstat.ip_overhead_download_rate;
	ss->total_ip_overhead_download = sstat.total_ip_overhead_download;
	ss->dht_upload_rate = sstat.dht_upload_rate;
	ss->dht_download_rate = sstat.dht_download_rate;
	ss->total_dht_download = (uint64_t) sstat.total_dht_download;
	ss->total_dht_upload = (uint64_t) sstat.total_dht_upload;
	ss->tracker_upload_rate = sstat.tracker_upload_rate;
	ss->tracker_download_rate = sstat.tracker_download_rate;
	ss->total_tracker_download = (uint64_t) sstat.total_tracker_download;
	ss->total_tracker_upload = (uint64_t) sstat.total_tracker_upload;
	ss->total_redundant_bytes = (uint64_t) sstat.total_redundant_bytes;
	ss->total_failed_bytes = (uint64_t) sstat.total_failed_bytes;
	ss->num_peers = sstat.num_peers;
	ss->num_unchoked = sstat.num_unchoked;
	ss->allowed_upload_slots = sstat.allowed_upload_slots;
	ss->up_bandwidth_queue = sstat.up_bandwidth_queue;
	ss->down_bandwidth_queue = sstat.down_bandwidth_queue;
	ss->optimistic_unchoke_counter = sstat.optimistic_unchoke_counter;
	ss->unchoke_counter = sstat.unchoke_counter;
	ss->disk_write_queue = sstat.disk_write_queue;
	ss->dht_nodes = sstat.dht_nodes;
	ss->dht_node_cache = sstat.dht_node_cache;
	ss->dht_torrents = sstat.dht_torrents;
	ss->dht_global_nodes = (uint64_t) sstat.dht_global_nodes;
	// TODO: active_requests and dht_routing_table
	ss->dht_total_allocations = sstat.dht_total_allocations;
	// TODO: utp_stats
	ss->peerlist_size = sstat.peerlist_size;
}

torrent_vector *lt_session_get_torrents(session *s) {
	static std::vector<libtorrent::torrent_handle> handles;
	libtorrent::session *ses;

	ses = reinterpret_cast<libtorrent::session*>(s); 
	handles = ses->get_torrents();
	return reinterpret_cast<torrent_vector*>(&handles);
}

void lt_session_set_alert_mask(session *s, uint32_t mask) {
	reinterpret_cast<libtorrent::session*>(s)->set_alert_mask(mask);
}

void lt_session_pop_alerts(session *s, alert_deque *ad) {
	libtorrent::session *ses = reinterpret_cast<libtorrent::session*>(s);
	std::deque<libtorrent::alert*> *dq
		= reinterpret_cast<std::deque<libtorrent::alert*>*>(ad);

	ses->pop_alerts(dq);	// fill with alerts
}

}
