#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "subirane.h"







// #define _GNU_SOURCE /* for asprintf */
// #include <stdio.h>
// #include <stdint.h>

// #if HAVE_CONFIG_H
// #include <config.h>
// #endif

// #include <linux/version.h>
// #include <linux/input.h>

// #include <string.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <dirent.h>
// #include <errno.h>
// #include <getopt.h>
// #include <ctype.h>
// #include <signal.h>
// #include <sys/time.h>
// #include <sys/types.h>
// #include <unistd.h>

// #include "subirane.h"

// #define BITS_PER_LONG (sizeof(long) * 8)
// #define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
// #define OFF(x)  ((x)%BITS_PER_LONG)
// #define BIT(x)  (1UL<<OFF(x))
// #define LONG(x) ((x)/BITS_PER_LONG)
// #define test_bit(bit, array)	((array[LONG(bit)] >> OFF(bit)) & 1)

// #define DEV_INPUT_EVENT "/dev/input"
// #define EVENT_DEV_NAME "event"

// #ifndef EV_SYN
// #define EV_SYN 0
// #endif
// #ifndef SYN_MAX
// #define SYN_MAX 3
// #define SYN_CNT (SYN_MAX + 1)
// #endif
// #ifndef SYN_MT_REPORT
// #define SYN_MT_REPORT 2
// #endif
// #ifndef SYN_DROPPED
// #define SYN_DROPPED 3
// #endif

// #define NAME_ELEMENT(element) [element] = #element

// enum evtest_mode {
// 	MODE_CAPTURE,
// 	MODE_QUERY,
// 	MODE_VERSION,
// };

// static const struct query_mode {
// 	const char *name;
// 	int event_type;
// 	int max;
// 	int rq;
// } query_modes[] = {
// 	{ "EV_KEY", EV_KEY, KEY_MAX, EVIOCGKEY(KEY_MAX) },
// 	{ "EV_LED", EV_LED, LED_MAX, EVIOCGLED(LED_MAX) },
// 	{ "EV_SND", EV_SND, SND_MAX, EVIOCGSND(SND_MAX) },
// 	{ "EV_SW",  EV_SW, SW_MAX, EVIOCGSW(SW_MAX) },
// };

// static int grab_flag = 0;
// static volatile sig_atomic_t stop = 0;

// static void interrupt_handler(int sig)
// {
// 	stop = 1;
// }


// /**
//  * Print usage information.
//  */
// static int usage(void)
// {
// 	printf("USAGE:\n");
// 	printf(" Capture mode:\n");
// 	printf("   %s [--grab] /dev/input/eventX\n", program_invocation_short_name);
// 	printf("     --grab  grab the device for exclusive access\n");
// 	printf("\n");
// 	printf(" Query mode: (check exit code)\n");
// 	printf("   %s --query /dev/input/eventX <type> <value>\n",
// 		program_invocation_short_name);

// 	printf("\n");
// 	printf("<type> is one of: EV_KEY, EV_SW, EV_LED, EV_SND\n");
// 	printf("<value> can either be a numerical value, or the textual name of the\n");
// 	printf("key/switch/LED/sound being queried (e.g. SW_DOCK).\n");

// 	return EXIT_FAILURE;
// }

// /**
//  * Filter for the AutoDevProbe scandir on /dev/input.
//  *
//  * @param dir The current directory entry provided by scandir.
//  *
//  * @return Non-zero if the given directory entry starts with "event", or zero
//  * otherwise.
//  */
// static int is_event_device(const struct dirent *dir) {
// 	return strncmp(EVENT_DEV_NAME, dir->d_name, 5) == 0;
// }
// /**
//  * Scans all /dev/input/event*, display them and ask the user which one to
//  * open.
//  *
//  * @return The event device file name of the device file selected. This
//  * string is allocated and must be freed by the caller.
//  */
// static char* scan_devices(void)
// {
// 	struct dirent **namelist;
// 	int i, ndev, devnum;
// 	char *filename;
// 	int max_device = 0;

// 	ndev = scandir(DEV_INPUT_EVENT, &namelist, is_event_device, versionsort);
// 	if (ndev <= 0)
// 		return NULL;

// 	fprintf(stderr, "Available devices:\n");

// 	for (i = 0; i < ndev; i++)
// 	{
// 		char fname[64];
// 		int fd = -1;
// 		char name[256] = "???";

// 		snprintf(fname, sizeof(fname),
// 			 "%s/%s", DEV_INPUT_EVENT, namelist[i]->d_name);
// 		fd = open(fname, O_RDONLY);
// 		if (fd < 0)
// 			continue;
// 		ioctl(fd, EVIOCGNAME(sizeof(name)), name);

// 		fprintf(stderr, "%s:	%s\n", fname, name);
// 		close(fd);

// 		sscanf(namelist[i]->d_name, "event%d", &devnum);
// 		if (devnum > max_device)
// 			max_device = devnum;

// 		free(namelist[i]);
// 	}

// 	fprintf(stderr, "Select the device event number [0-%d]: ", max_device);
// 	scanf("%d", &devnum);

// 	if (devnum > max_device || devnum < 0)
// 		return NULL;

// 	asprintf(&filename, "%s/%s%d",
// 		 DEV_INPUT_EVENT, EVENT_DEV_NAME,
// 		 devnum);

// 	return filename;
// }
// /**
//  * Enter capture mode. The requested event device will be monitored, and any
//  * captured events will be decoded and printed on the console.
//  *
//  * @param device The device to monitor, or NULL if the user should be prompted.
//  * @return 0 on success, non-zero on error.
//  */
// static int do_capture(const char *device, int grab_flag)
// {
// 	int fd;
// 	char *filename = NULL;

// 	if (!device) {
// 		fprintf(stderr, "No device specified, trying to scan all of %s/%s*\n",
// 			DEV_INPUT_EVENT, EVENT_DEV_NAME);

// 		if (getuid() != 0)
// 			fprintf(stderr, "Not running as root, no devices may be available.\n");

// 		filename = scan_devices();
// 		if (!filename)
// 			return usage();
// 	} else
// 		filename = strdup(device);

// 	if (!filename)
// 		return EXIT_FAILURE;

// 	if ((fd = open(filename, O_RDONLY)) < 0) {
// 		perror("evtest");
// 		if (errno == EACCES && getuid() != 0)
// 			fprintf(stderr, "You do not have access to %s. Try "
// 					"running as root instead.\n",
// 					filename);
// 		goto error;
// 	}

// 	if (!isatty(fileno(stdout)))
// 		setbuf(stdout, NULL);

// 	if (print_device_info(fd))
// 		goto error;

// 	printf("Testing ... (interrupt to exit)\n");

// 	if (test_grab(fd, grab_flag))
// 	{
// 		printf("***********************************************\n");
// 		printf("  This device is grabbed by another process.\n");
// 		printf("  No events are available to evtest while the\n"
// 		       "  other grab is active.\n");
// 		printf("  In most cases, this is caused by an X driver,\n"
// 		       "  try VT-switching and re-run evtest again.\n");
// 		printf("  Run the following command to see processes with\n"
// 		       "  an open fd on this device\n"
// 		       " \"fuser -v %s\"\n", filename);
// 		printf("***********************************************\n");
// 	}

// 	signal(SIGINT, interrupt_handler);
// 	signal(SIGTERM, interrupt_handler);

// 	free(filename);

// 	return print_events(fd);

// error:
// 	free(filename);
// 	return EXIT_FAILURE;
// }

















extern int do_capture(const char *device, int grab_flag);

/*******************************************
 * 
 * 
 * ****************************************/
void read_mouse(void * device)
{
    //do_capture("/dev/input/event5", 0);
    do_capture((char *)device, 0);


}
/*******************************************
 * 
 * 
 * ****************************************/
int main(int argc, char **argv) 
{

    printf("Start\n");
    int sub1 = argv[1][0]-0x30;
    int sub2 = atoi(argv[2]);
    printf("var1 = %d\n", sub1);
    printf("var2 = %d\n", sub2);
    //int res = calc_sum(sub1,sub2);

    int res;
    subirane sub;
    sub.sub1 = sub1;
    sub.sub2 = sub2;
    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, calc_sum, (void *)&sub);
    void * ressult = NULL;
    pthread_join(thread_id1, &ressult);

    printf("res = %d\n", (int *)ressult);


    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, read_mouse, (void *)"/dev/input/event5");

	pthread_t thread_id3;
    pthread_create(&thread_id3, NULL, read_mouse, (void *)"/dev/input/event11");

    pthread_join(thread_id2, NULL);
	pthread_join(thread_id3, NULL);

	printf("STOP\n");
    
    return 0;
}
