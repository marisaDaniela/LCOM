#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>
#include "test3.h"
#include "i8042.h"

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	sef_startup();
	sys_enable_iop(SELF);

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"test_scan <0 -> C, 1-> ASM>\"\n"
			"\t service run %s -args \"poll\"\n"
			"\t service run %s -args \"timed_scan <time>\"\n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short assembly, time;

	if (strncmp(argv[1], "test_scan", strlen("test_scan")) == 0) {
		if (argc != 3) {
			printf("test3: wrong no. of arguments for kbd_test_scan()\n");
			return 1;
		}
		assembly = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (assembly == ULONG_MAX){
			return 1;
		}
		printf("test3::kbd_test_scan(%d)\n", assembly);
		return kbd_test_scan(assembly);
	}
	else if (strncmp(argv[1], "poll", strlen("poll")) == 0) {
		if (argc != 2) {
			printf("test3: wrong no. of arguments for kbd_test_poll\n");
			return 1;
		}
		printf("test3::kbd_test_poll()\n");
		return kbd_test_poll();
	}
	else if (strncmp(argv[1], "timed_scan", strlen("timed_scan")) == 0) {
		if (argc != 3) {
			printf("test3: wrong no of arguments for timed_scan()\n");
			return 1;
		}
		time = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (time == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_timed_scan(%hu)\n", time);
		return kbd_test_timed_scan(time);
	}
	else {
		printf("test3: %s - no valid function!\n", argv[1]);
		return 1;
	}
}

static unsigned long parse_ulong(char *str, int base)
{
	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("test3: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
