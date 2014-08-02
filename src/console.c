// console.c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "console.h"

/* @gt_dbg(): sends a debug-level message to the client */
static void gt_dbg(const char *fmt, ...);

/* @gt_err(): sends an error-level message to the client */
static void gt_err(const char *fmt, ...);

/* @gt_get_ts(): gets the current time stamp */
static void gt_get_ts(char *str);

struct gt_console Console = {
	.debug = gt_dbg,
	.error = gt_err,
	.timestamp = gt_get_ts
};

static void gt_dbg(const char *fmt, ...) {
	va_list args;
	char temp[CONSOLE_MAX_TS_SIZE];

	gt_get_ts(temp);
	printf("["KGRN "%s"KNRM"]: ", temp);
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
}

static void gt_err(const char *fmt, ...) {
	va_list args;
	char temp[CONSOLE_MAX_TS_SIZE];

	gt_get_ts(temp);
	printf("["KRED"%s"KNRM"]: ", temp);
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
}

static void gt_get_ts(char *str) {
	time_t t = time(NULL);
	struct tm *lt = localtime(&t);
	*str = '\0';
	strftime(str, CONSOLE_MAX_TS_SIZE, "%Y-%b-%d @ %I:%M:%S", lt);
}
