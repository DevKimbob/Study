#include "json.h"

int **parse_json(char *filename, node_name **node, int *node_size, int *m_size);
void print_json(int **len_arr, int size);
int get_node_index(node_name *node, char *target, int size);
void free_arr(int **arr_ptr, int size);
void free_struct(node_name *node);

int **parse_json(char *filename, node_name **node, int *node_size, int *m_size) {
    json_object *pJsonObject = NULL;
    json_object *cJsonObject = NULL;
    int **len_arr = NULL;
    int n, m, node_cnt = 0;
    node_name *nptr;

    // open json file
    if ((pJsonObject = json_object_from_file(filename)) == NULL) {
        printf("Read from %s failed\n", filename);
        exit(1);
    }

    // set n, m
    n = json_object_get_int(json_object_object_get(pJsonObject, "node_count"));
    *node_size = n;
    m = json_object_get_int(json_object_object_get(pJsonObject, "path_count"));
    if (m_size != NULL)
        *m_size = m;

    // alloc len array
    len_arr = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        len_arr[i] = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                len_arr[i][j] = 0;
            else
                len_arr[i][j] = INF;
        }
    }

    // alloc name struct
    nptr = (node_name *)malloc(sizeof(node_name));
    *node = nptr;
    nptr->len = 0;
    nptr->node_ptr = (char **)malloc(sizeof(char *) * n);

    // set name struct
    cJsonObject = json_object_object_get(pJsonObject, "node");
    json_object_object_foreach(cJsonObject, key, val) {
        nptr->len++;
        nptr->node_ptr[node_cnt++] = key;
    }

    // set len array
    node_cnt = 0;
    json_object_object_foreach(cJsonObject, key_src, val_src) {
        json_object_object_foreach(val_src, key_dst, val_dst) {
            for (int i = 0; i < nptr->len; i++) {
                if (strcmp(nptr->node_ptr[i], key_dst) == 0) {
                    len_arr[node_cnt][i] = json_object_get_int(val_dst);
                    break;
                }
            }
        }
        node_cnt++;
    }

    return len_arr;
}

void print_json(int **len_arr, int size) {
    // print len array for test purposes
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (len_arr[i][j] != INF && len_arr[i][j]) 
                printf("%2d ", len_arr[i][j]);
            else
                printf(" . ");
        }
        puts("");
    }
}

int get_node_index(node_name *node, char *target, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(node->node_ptr[i], target) == 0)
            return i;
    }
    return -1;
}

void free_arr(int **arr_ptr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr_ptr[i]);
    }
    free(arr_ptr);
}

void free_struct(node_name *node) {
    free(node->node_ptr);
    free(node);
}