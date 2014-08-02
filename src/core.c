// core.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core.h"

int gt_core_is_maglink(const char *url) {
	return !strncmp("magnet:", url, 7);
}

char *gt_core_get_savepath(char *str) {
	// TODO: WIN32 specific functions
	if (!getenv("HOME")) return NULL;
	char *home = getenv("HOME");
	strcpy(str, home);
	strcat(str, "/Downloads");
	return str;
}
