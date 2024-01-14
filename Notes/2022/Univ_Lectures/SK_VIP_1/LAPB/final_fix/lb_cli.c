#include "sockhdr.h"

event get_event();
event get_primitive();
event fromtcp();
boolean comp_seq_number();
void totcp();
u_char *make_frame();
void senddata();
void sendpdu();
void increment_vs();

void sendpdu(acts)
action acts;
{
	u_field ctrl_field;
	u_char pval, *p, *pcast;

	if (acts == sabm) {
		ctrl_field.id = 3;  // 11(2)
		ctrl_field.response = 0;
		ctrl_field.pf = 0;
		ctrl_field.command = SABM;

		pcast = (u_char *)&ctrl_field;
		p = make_frame(1, pcast, 0, 0);
		totcp(p);
	}
	else if (acts == disc) {
		ctrl_field.id = 3;  // 11(2)
		ctrl_field.response = 0;
		ctrl_field.pf = 0;
		ctrl_field.command = DISC;

		pcast = (u_char *)&ctrl_field;
		p = make_frame(1, pcast, 0, 0);
		totcp(p);
	}
}

void senddata() {
	static u_char sendmesg[100];
	u_char pval, *p, *pcast;

	printf("Input any characters\n");
	// scanf("%s", sendmesg);
	fgets(sendmesg, 100, stdin);
	if (sendmesg[strlen(sendmesg) - 1] == '\n')
		sendmesg[strlen(sendmesg) - 1] = 0;

	data_ctrl_field.id = 0;
	data_ctrl_field.ns = vs;
	data_ctrl_field.pf = 0;
	data_ctrl_field.nr = 0;

	strcpy((char *)buffer[vs], sendmesg);
	pcast = (u_char *)&data_ctrl_field;
	p = make_frame(1, pcast, buffer[vs], strlen(buffer[vs]));
	totcp(p);
}

void print_binary(int n, int len) {
    int pwr_two = 1;
    int count = 0;

    while (n >= pwr_two) {
        pwr_two *= 2;
        count++;
    }
    if (count) {
        pwr_two /= 2;
        // count--;
    }

    // printf("n : %d, pwr_two : %d, count : %d\n", n, pwr_two, count);

    for (int i = 0; i < len - count; i++) {
        printf("0");
    }

    while (count) {
        if (n >= pwr_two) {
            printf("1");
            n -= pwr_two;
        }
        else {
            printf("0");
        }
        pwr_two /= 2;
        count--;
    }
    puts("");
}

int make_checksum(int target, int len) {
    int checksum = 0;
    int mask = 1;

    for (int i = 0; i < len; i++) {
        mask *= 2;
    }
    mask--;

    checksum = target;

    while (checksum > mask)
        checksum = (checksum & mask) + (checksum >> len);

    return checksum;
}

u_short make_crc(int target, int gx) {
	int mask = 32768;  // 1000_0000_0000_0000
	u_short crc;

	target <<= 6;
	gx <<= 9;
	crc = target;

	for (int i = 0; i < 10; i++) {
		if ((mask & target) == mask) {
			target ^= gx;
		}

		mask >>= 1;
		gx >>= 1;
	}

	crc |= target;
	return crc;
}

u_char *make_frame(address, ctrl_field, info, info_size)
u_char address, *ctrl_field, *info;
int info_size;
{
	int i;
	u_char *frame_pointer, *p, *q;
	int checksum = 0;

	frame_pointer = (u_char *)calloc(info_size + 6, sizeof(u_char));
	q = p = frame_pointer;
	*p = 126;  // flag 01111110
	*(++p) = address;
	*(++p) = *ctrl_field;
	p++;
	for (i = 0; i < info_size; ++i) {
		*p = *info;
		checksum += *info;  // checksum
		p++; info++;
	}
	checksum = make_checksum(checksum, 10);  // checksum : tcp
	if (info_size && verbose) {
		printf("** Created CRC **\n");
		printf("** DATA : ");
		print_binary(make_checksum(checksum, 10), 10);
		printf("** G(x) : ");;
		print_binary(GX, 7);
		printf("** CRC  : ");
		print_binary(make_crc(checksum, GX), 16);
	}
	*p = make_crc(checksum, GX) >> 8;  // checksum : crc first 8bits
	*(++p) = make_crc(checksum, GX);  // checksum : crc last 8bits
	*(++p) = 126;
	return frame_pointer;
}

void totcp(p)
u_char *p;
{
	int	i, n;
	static u_char sendmesg[100];
	
	n = strlen(buffer[vs]) + 6;
	for (i = 0; i < n; ++i) 
		sendmesg[i] = p[i];
	if (write(sockfd, (char *)sendmesg, n) != n) {
		printf("sendto error \n");
		exit(1);
	}
}

event fromtcp() {
	u_char	recv[100], field;
	int	n, id, s, res;
	s_field* sfld;
	u_field* ufld;
	
	if (read(sockfd, (char *)recv, 100) < 0) {
		printf("recvfrom error primary\n");
	}

	field = recv[2];
	sfld = (void *)&field;
	ufld = (void *)&field;
	id = sfld->id;
	if (id == 2) {
		nr = sfld->nr;
		s = sfld->s;
		if (s == RR) return rr_received;
	}
	else if (id == 3) {
		res = ufld->response;
		if (res == UA) return ua_received;
	}
	else {
		printf("Synchronization mismatching....\n");
		exit(1);
	}

	id = field & 3;
	if (id == 2) {
		nr = (field >> 5) & 7;
		s = (field >> 2) & 3;
		if (s == RR) return rr_received;
	}
	else if (id == 3) {
		s = (field >> 2) & 3;
		if (s == UA) return ua_received;
	}
	else {
		printf("Synchronization mismatching....\n");
		exit(1);
	}
}

boolean comp_seq_number() {
	int i;
	if (vs == nr) {
		for (i = 0; i < 100; ++i) 
			buffer[nr][i] = 0;
		return true;
	}
	else 
		return false;
}

event get_primitive() {
	static u_char c[20];

	printf("Input the intial character of following \n");
	printf(" (c)onnect \n");
	printf(" (d)isconnect \n");
	printf(" (i)nformation transfer \n");
	
	// scanf("%s", c);
	fgets(c, 20, stdin);
	switch (c[0]) {
		case 'c':
			return connect_req;
		case 'd':
			return disconnect_req;
		case 'i':
			return data_req;
	}
}

event get_event() {
	if ((current_state == disconnected) || (current_state == data_transfer))
		return get_primitive();
	else
		return fromtcp();
}

void increment_vs() {
	vs = ++count % 2;
	if (count == 9999) count = 0;
}

int main(argc, argv)
int argc;
char *argv[];
{
	struct sockaddr_in second_addr;
	struct hostent *hp;
	unsigned long inaddr;

	if (argc > 3) {
		if (argv[3][0] == 'v' || argv[3][0] == 'V')
			verbose = 1;
	}
	
	current_state = disconnected;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("LAPB Client Create Socket :");
		exit(1);
	}

	hp = gethostbyname(argv[1]);
	if (hp == 0) {
		printf("Unknow Host : %s\n", argv[1]);
		exit(2);
	}
	bcopy ((char *)hp->h_addr, (char *)&second_addr.sin_addr, hp->h_length);
	second_addr.sin_family = AF_INET;
	second_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sockfd, (struct sockaddr *)&second_addr, sizeof(second_addr)) < 0) {
		perror("Connecting Stream Socket");
		exit(1);
	}

	int select;
	while (1) {
		incoming_event = get_event();
		
		select = (int)current_state * 8 + (int)incoming_event;
		switch (select) {
			case 0:
				sendpdu((action)SABM);
				vputs("** SABM Sent");
				current_state = sabm_sent;
				vputs("** Current State : sabm_sent");
				printf("Connection now ...\n");
				break;
			case 9:
				current_state = data_transfer;
				vputs("** UA Received");
				vputs("** Current State : data_transfer\n");
				break;
			case 17:
				current_state = disconnected;
				vputs("** UA Received");
				vputs("** Current State : disconnected");
				exit(1);
			case 26:
				sendpdu((action)DISC);
				vputs("** DISC Sent");
				current_state = disc_sent;
				vputs("** Current State : disc_sent");
				printf("Disconnecting now ...\n");
				break;
			case 27:
				vputs("** Input DATA");
				senddata();
				vputs("** Sending DATA");
				increment_vs();
				vputs("** Incrementing vs");
				current_state = waiting_ack;
				vputs("** Current State : waiting_ack");
				printf("Sending information now ...\n");
				break;
			case 36:
				vputs("** RR Received");
				vputs("** Comparing Sequence Number");
				if (comp_seq_number() == true) {
					retrans_count = 0;
				}
				else {
					printf("sequence number mismatching.\n");
					err_count++;
				}
				current_state = data_transfer;
				vputs("** Current State : data_trasnfer");
				printf("Returning to Data transfer state now ...\n\n");
				break;
			default:
				printf("invalid transition\n");
				err_count++;
				break;
		}
	}
}
