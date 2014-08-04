// core.h
#ifndef CORE_H
#define CORE_H

#include "torrent.h"
#include "alerts.h"
#include "wrappers/libtorrent.h"

#define GT_CORE_DEFAULT_PORTS() 6881, 6889

/* @gt_core_is_maglink(): verifies whether or not a url is a magnet link */
int 		gt_core_is_maglink		(const char *url);

/* @gt_core_get_savepath(): gets the default user save directory */
char 		*gt_core_get_savepath		(char *str);

/* @gt_core_session_start(): starts gtorrent session and takes care of
 * libtorrent functionality. x and y are default listening ports */
void		gt_core_session_start		(int x, int y);

/* @gt_core_session_end(): ends gtorrent session. This must be called
 * explicitly upon program termination. */
void		gt_core_session_end		(void);

/* @gt_core_session_set_callback(): sets the callback function for whenever an
 * alert is popped that is relevant to the session only (the alert is not a 
 * torrent_alert). */
void		gt_core_session_set_callback	(int (*f)(gt_alert *));

/* @gt_core_session_remove_callback(): remove callback function for session */
void		gt_core_session_remove_callback	(void);

/* @gt_core_session_add_torrent(): adds a torrent item to the session. After
 * calling this action, the torrent handle (t-th) of the simple torrent struct
 * is immediately modified. Returns 0 on failure, 1 on success. */
int		gt_core_session_add_torrent	(gt_torrent *t);

/* @gt_core_session_remove_torrent(): removes a torrent from the session and
 * returns the same pointer to that torrent as was provided, or NULL on
 * error. */
gt_torrent	*gt_core_session_remove_torrent	(gt_torrent *t);

/* @gt_core_session_update(): pops all alert messages from the session and
 * invokes the appropriate callback functions attached to the session and
 * individual torrent objects. */
int		gt_core_session_update		(void);

#endif
