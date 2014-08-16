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
	char			*url;	// magnet/http link (if ti is NULL)
	int	(*call)(gt_alert *);	// alert callback
	void			*data;	// custom data to hold in gt_torrent
	gt_torrent		*next;	// pointer to next item in list
} gt_torrent;

/* @gt_trnt_gettime(): converts seconds to "xd xh xm xs" format */
void		gt_trnt_gettime		(uint64_t t, char *s);

/* @gt_trnt_getfsize(): converts raw file size to string format */
void 		gt_trnt_getfsize	(uint64_t fsize, char *s);

/* @gt_trnt_getfsizep(): getfsize(), but with precision */
void		gt_trnt_getfsizep	(uint64_t fsize, int p, char *s);

/* @gt_trnt_getrate(): converts raw rate in bytes/s to string format */
void		gt_trnt_getrate		(uint64_t rsize, char *s);

/* @gt_trnt_getratep(): getrate(), but with precision */
void		gt_trnt_getratep	(uint64_t rsize, int p, char *s);

/* @gt_trnt_getstate(): converts state value to string format */
void		gt_trnt_getstate	(enum torrent_state state, char *s);

/* @gt_trnt_geteta(): approximates estimated time (in sec) remaining */
uint64_t	gt_trnt_geteta		(uint64_t rate, uint64_t done, 
					 uint64_t total);

/* @gt_trnt_geteta_fmt(): format ETA (in seconds) to string */
void		gt_trnt_geteta_fmt	(char *s, uint64_t sec);

/* @gt_trnt_create(): create a simple gt_torrent from a file (possible magnet
 * link or local file) and a save path for the downloaded data. */
gt_torrent	*gt_trnt_create		(const char *file,
					 const char *save_path);

/* @gt_trnt_destroy(): delete a gt_torrent. Note that the next member is not
 * destroyed, and is only done so automatically if the torrent is on the list
 * that is freed when gt_core_session_end() is called. */
void		gt_trnt_destroy		(gt_torrent *t);

#endif
