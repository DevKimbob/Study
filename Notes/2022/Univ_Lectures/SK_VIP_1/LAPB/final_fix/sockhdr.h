#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdlib.h>
#include <unistd.h>

#define SERV_PORT 7000

#define	SABM 0
#define	UA 1
#define	DISC 2
#define	RR 3

#define GX 102

#define vputs(format) { \
	if (verbose) \
		puts(format); \
}

typedef enum {sabm, ua, disc, rr} action;
typedef enum {disconnected, sabm_sent, disc_sent, data_transfer, waiting_ack, data_waiting} state;
typedef enum {connect_req, ua_received, disconnect_req, data_req, rr_received, sabm_received, disc_received, data_received} event;
typedef enum {false, true} boolean;

static u_int retrans_count;
static event incoming_event;
static state current_state;
static u_char buffer[2][100];
static int vs = 0;
static int vr = 0;
static int ns = 0;
static int nr = 0;
static u_int count = 0;
static u_int err_count = 0;
static int sockfd, newsockfd;

static int checkerr = 0;
static int verbose = 0;

typedef struct {
	u_char	id:1, ns:3, pf:1, nr:3;
} i_field;

typedef struct {
	u_char	id:2, s:2, pf:1, nr:3;
} s_field;

typedef struct {
	u_char id:2, response:2, pf:1 , command:3;
} u_field;

static i_field data_ctrl_field;
