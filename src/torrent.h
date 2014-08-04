// torrent.h
#ifndef TORRENT_H
#define TORRENT_H

#include <inttypes.h>
#include "alerts.h"
#include "wrappers/libtorrent.h"

typedef struct gt_trnt {	// simplified torrent object
	torrent_params		*tp;
	torrent_info		*ti;
	torrent_handle		*th;
	int	(*call)(gt_alert *);	// alert callback
	gt_torrent		*next;	// pointer to next item in list
} gt_torrent;

/* @gt_trnt_gettime(): converts seconds to "xd xh xm xs" format */
void		gt_trnt_gettime		(uint64_t t, char *s);

/* @gt_trnt_getfsize(): converts raw file size to string format */
void 		gt_trnt_getfsize	(uint64_t fsize, char *s);

/* @gt_trnt_getrate(): converts raw rate in bytes/s to string format */
void		gt_trnt_getrate		(uint64_t rsize, char *s);

/* @gt_trnt_getstate(): converts state value to string format */
void		gt_trnt_getstate	(enum torrent_state state, char *s);

/* @gt_trnt_create(): create a simple gt_torrent from a file (possible magnet
 * link) and a save path for the downloaded data. */
gt_torrent	*gt_trnt_create		(char *file, char *save_path);

/* @gt_trnt_destroy(): delete a gt_torrent */
void		gt_trnt_destroy		(gt_torrent *t);

#endif
