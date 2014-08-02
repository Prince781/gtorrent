// core.h
#ifndef CORE_H
#define CORE_H

#include "torrent.h"

/* @gt_core_is_maglink(): verifies whether or not a url is a magnet link */
int 		gt_core_is_maglink		(const char *url);

/* @gt_core_get_savepath(): gets the default user save directory */
char 		*gt_core_get_savepath		(char *str);

#endif
