// torrent.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "torrent.h"
#include "console.h"
#include "core.h"

// rate speeds are in multiples of 1000
#define KILOBYTE	1000
#define MEGABYTE	1000000
#define GIGABYTE	1000000000
#define TERABYTE	1000000000000

// time blocks in seconds
#define WEEK	604800
#define DAY	86400
#define HOUR	3600
#define MINUTE	60

// not auto-managed by default
static uint64_t default_flags = /* flag_paused | */flag_update_subscribe
				| flag_duplicate_is_error;

/* @default_trnt_callback: default callback for torrents */
static int default_trnt_callback(gt_alert *a);

void gt_trnt_gettime(uint64_t t, char *s) {
	sprintf(s, "%"PRIu64"d %"PRIu64"h %"PRIu64"m %"PRIu64"s",
		t/86400, (t/3600)%24, (t/60)%60, t%60);
}

void gt_trnt_getfsize(uint64_t fsize, char *s) {
	gt_trnt_getfsizep(fsize, 4, s);
}

void gt_trnt_getfsizep(uint64_t fsize, int p, char *s) {
	if (fsize / TERABYTE)
		sprintf(s, "%.*g TB", p, fsize / (double)TERABYTE);
	else if (fsize / GIGABYTE)
		sprintf(s, "%.*g GB", p, fsize / (double)GIGABYTE);
	else if (fsize / MEGABYTE)
		sprintf(s, "%.*g MB", p, fsize / (double)MEGABYTE);
	else if (fsize / KILOBYTE)
		sprintf(s, "%.*g kB", p, fsize / (double)KILOBYTE);
	else
		sprintf(s, "%u B", (unsigned) fsize);
}

void gt_trnt_getrate(uint64_t rsize, char *s) {
	gt_trnt_getfsize(rsize, s);
	strcat(s, "/s");
}

void gt_trnt_getratep(uint64_t rsize, int p, char *s) {
	gt_trnt_getfsizep(rsize, p, s);
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

uint64_t gt_trnt_geteta(uint64_t rate, uint64_t done, uint64_t total) {
	return (total - done) / (rate == 0 ? 1 : rate);
}

void gt_trnt_geteta_fmt(char *s, uint64_t sec) {
	*s = '\0';
	if (sec / WEEK) {
		s += sprintf(s,
			sec/WEEK > 1 ? "%"PRIu64" weeks, ":"%"PRIu64" week, ",
			sec/WEEK);
		sec %= WEEK;
	}
	if (sec / DAY) {
		s += sprintf(s,
			sec/DAY > 1 ? "%"PRIu64" days, " : "%"PRIu64" day, ",
			sec/DAY);
		sec %= DAY;
	}
	if (sec / HOUR) {
		s += sprintf(s,
			sec/HOUR > 1 ? "%"PRIu64" hrs, " : "%"PRIu64" hr, ",
			sec/HOUR);
		sec %= HOUR;
	}
	if (sec / MINUTE) {
		s += sprintf(s, "%"PRIu64" min, ", sec/MINUTE);
		sec %= MINUTE;
	}
	sprintf(s, "%"PRIu64" sec", sec);
}

gt_torrent *gt_trnt_create(const char *file, char *save_path) {
	gt_torrent *gtp;
	char savepath[1024];

	if ((gtp = (gt_torrent *)malloc(sizeof(gt_torrent))) == NULL)
		return NULL;
	gtp->tp = NULL;
	gtp->ti = NULL;
	gtp->th = NULL;
	gtp->url = NULL;
	gtp->call = NULL;
	gtp->data = NULL;
	gtp->next = NULL;

	gtp->tp = lt_trnt_params_create();
	if (gt_core_is_maglink(file)) {
		gtp->url = strdup(file);
		gtp->ti = NULL;
	} else {
		gtp->ti = lt_trnt_info_create(file);
		gtp->url = NULL;
		if (gtp->ti == NULL) {
			Console.error("%s: Could not create torrent.",
				      "gt_trnt_create");
			gt_trnt_destroy(gtp);
			return NULL;
		}
	}

	if (save_path != NULL)
		lt_trnt_params_set_savepath(gtp->tp, save_path);
	else {
		lt_trnt_params_set_savepath(gtp->tp,
			gt_core_get_savepath(savepath));
		save_path = savepath;
	}

	if (gtp->url != NULL) {
		Console.debug("Saving torrent in directory %s...", save_path);
		lt_trnt_params_set_url(gtp->tp, gtp->url);
	} else {
		Console.debug("Saving %s in directory %s...", file, save_path);
		lt_trnt_params_set_info(gtp->tp, gtp->ti);
	}
	lt_trnt_params_set_flags(gtp->tp, default_flags);
	gtp->call = default_trnt_callback;

	return gtp;
}

void gt_trnt_destroy(gt_torrent *t) {
	if (t->tp != NULL)
		lt_trnt_params_destroy(t->tp);
	if (t->url != NULL)
		free(t->url);
	if (t->th != NULL)
		lt_trnt_handle_destroy(t->th);
	free(t);
}

static int default_trnt_callback(gt_alert *a) {
	Console.debug("Default alert for torrent %s",
		lt_trnt_params_get_name(a->trnt->tp));
	return 1;
}
