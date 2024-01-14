#ifndef _JSON_H_
#define _JSON_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <json-c/json.h>

#define INF 1<<10

typedef struct node_name {
    int len;
    char **node_ptr;
} node_name;

#endif