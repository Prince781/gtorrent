// stats.h
#ifndef UI_STATS_H
#define UI_STATS_H

#define STATSIZE 120	// number of items in list (seconds of history * 2)

struct sess_stat {	// simple structure containing some data at an interval
	int			val;
	struct sess_stat	*next;
};

/* @gt_gui_get_stat(): returns the start position of the stat list */
struct sess_stat	*gt_gui_get_stat	(void);

/* @gt_gui_stat_update(): updates status with more data */
void			gt_gui_stat_update	(void);

/* @gt_gui_stat_destroy(): free all memory */
void			gt_gui_stat_destroy	(void);

#endif
