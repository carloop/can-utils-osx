/**
 * slcand.c - userspace daemon for serial line CAN interface driver SLCAN
 * rewritten from it's original source in C to the OS X.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/tty.h>
#include <sys/sockio.h>

/* Daemon name */
#define DAEMON_NAME "slcandx"

/* Run under this specific user */
#define RUN_AS_USER "root"

/* The length of ttypath buffer */
#define TTYPATH_LENGTH 64

/* UART flow control types */
#define FLOW_NONE 0
#define FLOW_HW   1
#define FLOW_SW   2

void print_usage(char *prg)
{
    fprintf(stderr, "\nUsage: %s <tty> <canif-name>\n\n", prg);
    exit(EXIT_FAILURE);
}

static int slcand_running;
static int exit_code;
static char ttypath[TTYPATH_LENGTH];

int main(int argc, char *argv[])
{
    char *tty = NULL;
    char const *devprefix = "/dev";
    char *name = NULL;
    char buf[IFNAMSIZ+1];
}
