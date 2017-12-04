#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>
#include "test5.h"

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
			"\t service run %s -args \"test_init < mode, delay >\"\n"
			"\t service run %s -args \"test_square < x, y, size, color >\"\n"
			"\t service run %s -args \"test_line < xi, yi, xf, yf, color >\"\n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short mode, delay;
	unsigned short x, y, size;
	unsigned short xi, yi, xf, yf;
	unsigned long color;

	if (strncmp(argv[1], "test_init", strlen("test_init")) == 0) {
		if (argc != 4) {
			printf("lab5::wrong no. of arguments for video_test_init()\n");
			return 1;
		}
		mode = parse_ulong(argv[2], 16);						/* Parses string to unsigned long */
		if (mode == ULONG_MAX){
			return 1;
		}
		delay = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
		if (delay == ULONG_MAX){
			return 1;
		}
		printf("lab5::video_test_init(%d, %d)\n", mode, delay);
		return video_test_init(mode, delay);
	}
	else if (strncmp(argv[1], "test_square", strlen("test_square")) == 0) {
		if (argc != 6) {
			printf("lab5: wrong no. of arguments for video_test_square\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);
		if(x == ULONG_MAX)
			return 1;

		y = parse_ulong(argv[3], 10);
		if(y == ULONG_MAX)
			return 1;

		size = parse_ulong(argv[4], 10);
		if(size == ULONG_MAX)
			return 1;

		color = parse_ulong(argv[5], 10);
		if(color == ULONG_MAX)
			return 1;

		printf("lab5::video_test_square(%d,%d,%d,%d)\n", x, y, size, color);

		return video_test_square(x, y, size, color);
	}
	else if (strncmp(argv[1], "test_line", strlen("test_line")) == 0) {
		if (argc != 7) {
			printf("lab5: wrong no of arguments for video_test_line()\n");
			return 1;
		}
		xi = parse_ulong(argv[2], 10);
		if(xi == ULONG_MAX)
			return 1;

		yi = parse_ulong(argv[3], 10);
		if(yi == ULONG_MAX)
			return 1;
		xf = parse_ulong(argv[4], 10);
		if(xf == ULONG_MAX)
			return 1;

		yf = parse_ulong(argv[5], 10);
		if(yf == ULONG_MAX)
			return 1;

		color = parse_ulong(argv[6], 10);
		if(color == ULONG_MAX)
			return 1;

		printf("lab5::video_test_line(%d, %d, %d, %d, %d)\n",xi, yi, xf, yf, color);
		return video_test_line(xi, yi, xf, yf, color);
	}

	else {
		printf("lab5: %s - no valid function!\n", argv[1]);
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
