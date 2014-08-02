// torrent.h
#ifndef TORRENT_H
#define TORRENT_H

#include <inttypes.h>
#include "wrappers/libtorrent.h"

/* @gt_trnt_gettime(): converts seconds to "xd xh xm xs" format */
void		gt_trnt_gettime		(uint64_t t, char *s);

/* @gt_trnt_getfsize(): converts raw file size to string format */
void 		gt_trnt_getfsize	(uint64_t fsize, char *s);

/* @gt_trnt_getrate(): converts raw rate in bytes/s to string format */
void		gt_trnt_getrate		(uint64_t rsize, char *s);

/* @gt_trnt_listen(): attach a listener for torrent progress */
void		gt_trnt_listen	(session *s, int (*f)(session *));

#endif
