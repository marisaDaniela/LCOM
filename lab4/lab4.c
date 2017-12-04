#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>
#include "test4.h"

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	sef_startup();

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);

	return 0;
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"test_packet < number of packets >\"\n"
			"\t service run %s -args \"test_async < number of seconds (timeout) >\"\n"
			"\t service run %s -args \"test_remote < period, number of packets >\"\n"
			"\t service run %s -args \"test_gesture < length >\"\n",
			argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned long args;
	unsigned long period;

	if (strncmp(argv[1], "test_packet", strlen("test_packet")) == 0) {
		if (argc != 3) {
			printf("test4: wrong no. of arguments for mouse_test_packet()\n");
			return 1;
		}
		args = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (args == ULONG_MAX){
			return 1;
		}
		printf("test4::mouse_test_packet(%d)\n", args);
		return mouse_test_packet(args);
	}
	else if (strncmp(argv[1], "test_async", strlen("test_async")) == 0) {
		if (argc != 3) {
			printf("test4: wrong no. of arguments for mouse_test_async\n");
			return 1;
		}
		args = parse_ulong(argv[2], 10);

		if(args == ULONG_MAX)
			return 1;

		printf("test4::mouse_test_async(%d)\n", args);

		return mouse_test_async(args);
	}
	else if (strncmp(argv[1], "test_remote", strlen("test_remote")) == 0) {
		if (argc != 4) {
			printf("test4: wrong no of arguments for test_remote()\n");
			return 1;
		}
		period = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (period == ULONG_MAX)
			return 1;

		args = parse_ulong(argv[3], 10);
		if (args == ULONG_MAX)
			return 1;
		printf("test4::mouse_test_remote(%d, %d)\n", period, args);
		return mouse_test_remote(period, args);
	}
	else if (strncmp(argv[1], "test_gesture", strlen("test_gesture")) == 0) {
		if (argc != 3) {
			printf("test4: wrong no. of arguments for mouse_test_gesture\n");
			return 1;
		}
		args = parse_ulong(argv[2], 10);

		if(args == ULONG_MAX)
			return 1;

		printf("test4::mouse_test_gesture(%d)\n", args);

		return mouse_test_gesture(args);
	}

	else {
		printf("test4: %s - no valid function!\n", argv[1]);
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
