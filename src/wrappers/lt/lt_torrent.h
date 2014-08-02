#ifndef LT_TORRENT_H
#define LT_TORRENT_H

struct trnt_params;	// libtorrent::add_torrent_params
typedef struct trnt_params trnt_params;

struct trnt_info;	// libtorrent::torrent_info
typedef struct trnt_info trnt_info;

/* @lt_trnt_params_create(): create a new trnt_params */
trnt_params	*lt_trnt_params_create		(void);

/* @lt_trnt_params_set_savepath(): set savepath when torrent is finished */
void		lt_trnt_params_set_savepath	(trnt_params *tp, char *path);

/* @lt_trnt_info_create(): create torrent info from torrent file location */
trnt_info	*lt_trnt_info_create		(char *path);

/* @lt_trnt_params_set_info(): set torrent info of trnt_params */
void		lt_trnt_params_set_info	(trnt_params *tp, trnt_info *ti);

#endif
