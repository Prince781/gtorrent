// torrent.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "torrent.h"

// rate speeds are in multiples of 1000
#define KILOBYTE	1000
#define MEGABYTE	1000000
#define GIGABYTE	1000000000
#define TERABYTE	1000000000000

void gt_trnt_gettime(uint64_t t, char *s) {
	sprintf(s, "%"PRIu64"d %"PRIu64"h %"PRIu64"m %"PRIu64"s",
		t/86400, (t/3600)%24, (t/60)%60, t%60);
}

void gt_trnt_getfsize(uint64_t fsize, char *s) {
	if (fsize / TERABYTE)
		sprintf(s, "%.3lf TB", fsize / (double)TERABYTE);
	else if (fsize / GIGABYTE)
		sprintf(s, "%.3lf GB", fsize / (double)GIGABYTE);
	else if (fsize / MEGABYTE)
		sprintf(s, "%.3lf MB", fsize / (double)MEGABYTE);
	else if (fsize / KILOBYTE)
		sprintf(s, "%.3lf kB", fsize / (double)KILOBYTE);
	else
		sprintf(s, "%u B", (unsigned) fsize);
}

void gt_trnt_getrate(uint64_t rsize, char *s) {
	gt_trnt_getfsize(rsize, s);
	strcat(s, "/s");
}

void gt_trnt_getstate(enum torrent_state state, char *s) {
	switch (state) {
		case queued_for_checking:
			strcpy(s, "queued for checking");
			break;
		case checking_files:
			strcpy(s, "checking files");
			break;
		case downloading_metadata:
			strcpy(s, "downloading metadata");
			break;
		case downloading:
			strcpy(s, "downloading");
			break;
		case finished:
			strcpy(s, "finished");
			break;
		case seeding:
			strcpy(s, "seeding");
			break;
		case allocating:
			strcpy(s, "allocating");
			break;
		case checking_resume_data:
			strcpy(s, "checking resume data");
			break;
		default:
			strcpy(s, "unknown");
			break;
	}
}

void gt_trnt_listen(session *s, int (*f)(session *)) {
	struct timespec ntime = { .tv_sec = 0, .tv_nsec = 500000000l }, rem;

	while ((*f)(s))
		nanosleep(&ntime, &rem);
}
