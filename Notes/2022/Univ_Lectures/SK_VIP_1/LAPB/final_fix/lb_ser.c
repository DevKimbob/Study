#include "sockhdr.h"

event fromtcp();
boolean comp_seq_number();
void totcp();
u_char *make_frame();
void sendpdu();
void increment_vr();
void data_indicate();

void sendpdu(acts) 
action acts;
{
	u_field u_ctrl_field;
	s_field s_ctrl_field;
	u_char pval, *p, *pcast;

	if (acts == ua) {
		u_ctrl_field.id = 3;  // 11(2)
		u_ctrl_field.response = UA;
		u_ctrl_field.pf = 0;
		u_ctrl_field.command = 0;

		pcast = (u_char *) &u_ctrl_field;
		p = make_frame(3, pcast, 0, 0);
		totcp(p);
	}
	else if (acts == rr) {
		s_ctrl_field.id = 2;  // 10(2)
		s_ctrl_field.s = RR;
		s_ctrl_field.pf = 0;
		s_ctrl_field.nr = vr;

		pcast = (u_char *) &s_ctrl_field;
		p = make_frame(3, pcast, 0, 0);
		totcp(p);
	}
}

u_char *make_frame(address, ctrl_field, info, info_size)
u_char address, *ctrl_field, *info;
int info_size;
{
	int i;
	u_char *frame_pointer, *p;

	frame_pointer = (u_char *)calloc(info_size + 5, sizeof(u_char));
	p = frame_pointer;
	*p = 126;  // flag 01111110
	*(++p) = address;
	*(++p) = *ctrl_field;
	p++;
	for ( i = 0; i < info_size; ++i) {
		*p = *info;
		p++; info++;
	}
	*(++p) = 126;
	return frame_pointer;
}

void totcp(p)
u_char *p;
{
	int	n;

	n = strlen((char *)p);
	if (write(newsockfd, (char *)p, n) != n) {
		printf("sendto error \n");
		exit(1);
	}
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

int check_crc(int target, int gx) {
	int mask = 32768;

	gx <<= 9;

	for (int i = 0; i < 10; i++) {
		if ((mask & target) == mask) {
			target ^= gx;
		}

		mask >>= 1;
		gx >>= 1;
	}

	return (target == 0);
}

event fromtcp() {
	static u_char recv_arr[100], field;
	int id, cmd, i, length;
	int checksum = 0;
	int crc = 0;
	i_field* ifld;
	u_field* ufld;
	
	if ((length = read(newsockfd, (char *)recv_arr, 100)) < 0) {
		printf("recvfrom error \n");
		exit(1);
	}

	field = recv_arr[2];
	ifld = (void *)&field;
	ufld = (void *)&field;
	id = ifld->id;
	if (id == 0) {
		ns = ifld->ns;
		for (i = 0; i < 100; ++i) 
			buffer[vr][i] = 0;
		for (i = 3; i < length - 3; ++i) {
			buffer[vr][i-3] = recv_arr[i];
			checksum += recv_arr[i];
		}

		crc = (recv_arr[i] << 8) + recv_arr[i + 1];
		if (verbose) {
			printf("** Received CRC **\n");
			printf("** CRC : ");
			print_binary(crc, 16);
		}
		if (((crc >> 6) == make_checksum(checksum, 10)) && (check_crc(crc, GX) == 1)) {
			checkerr = 0;
		}
		else {
			checkerr = 1;
			puts("checksum error");
		}

		return data_received;
	}
	else {
		id = ufld->id;
		if (id == 3) {
			cmd = ufld->command;
			if (cmd == SABM) 
				return sabm_received;
			else if (cmd == DISC) 
				return disc_received;
		}
		else {
			printf("invaild frame received....\n");
			exit(1);
		}
	}

	// id = field & 1;
	// if (id == 0) {
	// 	ns = (field >> 1) & 7;
	// 	for (i = 0; i < 100; ++i) 
	// 		buffer[vr][i] = 0;
	// 	for (i = 3; i < length - 2; ++i) {
	// 		buffer[vr][i-3] = recv_arr[i];
	// 		checksum += recv_arr[i];
	// 	}

	// 	if ((checksum + recv_arr[i]) != 255) {
	// 		checkerr = 1;
	// 	}
	// 	else
	// 		checkerr = 0;

	// 	return data_received;
	// }
	// else {
	// 	id = field & 3;
	// 	if (id == 3) {
	// 		cmd = (field >> 5) & 7;
	// 		if (cmd == SABM) 
	// 			return sabm_received;
	// 		else if (cmd == DISC) 
	// 			return disc_received;
	// 	}
	// 	else {
	// 		printf("invaild frame received....\n");
	// 		exit(1);
	// 	}
	// }
}

void data_indicate() {
	printf("Received message : %s\n", buffer[vr]);
}

void increment_vr() {
	vr = ++count % 2;
	if (count == 9999) count = 0;
}

int main(argc, argv)
int argc;
char *argv[];
{
	int clilen, length;
	struct sockaddr_in	second_addr, cli_addr;
	
	if (argc > 1) {
		if ((argv[1][0] == 'v') || (argv[1][0] == 'V'))
			verbose = 1;
	}
	
	current_state = disconnected;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("can't open stream socket\n");
		exit(1);
	}
	
	bzero((char *) &second_addr, sizeof(second_addr));
	second_addr.sin_family = AF_INET;
	second_addr.sin_addr.s_addr = INADDR_ANY;
	second_addr.sin_port = 0;
	
	if (bind(sockfd, (struct sockaddr *) &second_addr, sizeof(second_addr)) < 0) {
		perror("Server bind socket :");
		exit(1);
	}

	length = sizeof(second_addr);
	if (getsockname(sockfd, (struct sockaddr *) &second_addr, &length) < 0) {
		perror("Getting sock name");
		exit(2);
	}
	printf("LAPB Socket Port Number %d\n", ntohs(second_addr.sin_port));

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		printf("accept error!\n");
		exit(1);
	}
	
	int err_count, select;
	while (1) {
		err_count = 0;
		
		incoming_event = fromtcp();
		select = (int)current_state * 8 + (int)incoming_event;
		switch (select) {
			case 5:
				vputs("** SABM Received");
				sendpdu((action)UA);
				vputs("** UA Sent");
				current_state = data_waiting;
				vputs("** Current State : data_waiting");
				printf("Waiting data....\n");
				break;
			case 46:
				sendpdu((action)UA);
				vputs("\n** DISC Received");
				vputs("** UA Sent");
				current_state = disconnected;
				vputs("** Current State : disconnected");
				printf("Disconnected right now ...\n");
				exit(1);
			case 47:
				if (ns == vr) {
					vputs("\n** DATA Received");
					vputs("** Indicating DATA");
					data_indicate();
					vputs("** Incrementing vr");
					increment_vr();
					sendpdu((action)RR);
					vputs("** RR Sent");
					printf("Waiting data....\n");
				}
				else {
					printf("sequence number mismatching.\n");
					err_count++;
				}
				break;
			default:
				printf("invalid transition\n");
				err_count++;
				current_state = disconnected;
				break;
		}
	}
}
