#ifndef _SFTP_H
#define _SFTP_H

#define MAX_LINE 80
#define MAX_PAGE 1024
#define SERV_TCP_PORT 0
#define HASH_LENGTH 20

typedef struct struct_header {
    int datalen;
    char cmd;
} header;

#endif