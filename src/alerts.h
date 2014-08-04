// alerts.h
#ifndef ALERTS_H
#define ALERTS_H

#include "wrappers/libtorrent.h"

typedef struct gt_trnt gt_torrent;

struct gt_alrt {	// simple gt_alert structure
	session		*ses;
	gt_torrent	*trnt;
	alert		*al;	// more-complex alert object pointer
	enum alert_type	type;	// simple alert type
};

typedef struct gt_alrt gt_alert;
#endif
