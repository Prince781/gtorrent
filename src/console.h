// console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#define CONSOLE_MAX_TS_SIZE	100
#define KNRM	"\x1B[0m"	// normal console color
#define KRED	"\x1B[31m"
#define KGRN	"\x1B[32m"
#define KYEL	"\x1B[33m"
#define KBLU	"\x1B[34m"
#define KMAG	"\x1B[35m"
#define KCYN	"\x1B[36m"
#define KWHT	"\x1B[37m"
#define KRST	"\033[0m"	// resets to previous console color
extern struct gt_console {
	void (*debug)(const char *, ...);
	void (*error)(const char *, ...);
	void (*timestamp)(char *);
} Console;

#endif
