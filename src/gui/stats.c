// stats.c
#include "stats.h"
#include "../core.h"
#include <stdlib.h>

static struct sess_stat *base, **p = &base;

static void init_base(void);
static void free_base(struct sess_stat **p);

struct sess_stat *gt_gui_get_stat(void) {
	return *p;
}

void gt_gui_stat_update(void) {
	session_status *status;
	
	if (base == NULL)
		init_base();
	status = lt_session_get_status(gt_core_get_session());
	(*p)->val = status->payload_download_rate;
	p = &(*p)->next;
}

void gt_gui_stat_destroy(void) {
	free_base(&base);
}

static void init_base(void) {
	int i;
	
	for (i=0; i<STATSIZE; ++i) {
		*p = malloc(sizeof(struct sess_stat));
		(*p)->val = 0;
		(*p)->next = NULL;
		p = &(*p)->next;
	}
	*p = base;
}

static void free_base(struct sess_stat **p) {
	if ((*p)->next != base)
		free_base(&(*p)->next);
	free(*p);
	*p = NULL;
}
