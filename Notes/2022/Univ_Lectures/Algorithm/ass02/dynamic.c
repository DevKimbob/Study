#include "json.h"

int **len_arr;

extern int **parse_json(char *, node_name **, int *, int *);
extern void print_json(int **, int);
extern int get_node_index(node_name *, char *, int);
extern void free_arr(int **, int);
extern void free_struct(node_name *);

void floyd(int start, int node_size) {
    for (int k = 0; k < node_size; k++) {
        for (int i = 0; i < node_size; i++) {
            for (int j = 0; j < node_size; j++) {
                    if (len_arr[i][j] > len_arr[i][k] + len_arr[k][j])
                        len_arr[i][j] = len_arr[i][k] + len_arr[k][j];
            }
        }
    }
}

int main() {
    char *filename = "./path.json";
    char *start = "Seoul";
    int node_size, index, min;
    node_name *node;

    // read and parse json file
    len_arr = parse_json(filename, &node, &node_size, NULL);
    puts("== Graph of the given nodes ==");
    print_json(len_arr, node_size);
    puts("");

    // greedy algorithm
    index = get_node_index(node, start, node_size);
    floyd(index, node_size);

    // result
    puts("== Graph of the sortest paths ==");
    print_json(len_arr, node_size);
    puts("");

    printf("== Distances from %s ==\n", start);
    for (int i = 0; i < node_size; i++) {
        if (i != index) {
            printf("%s : ", node->node_ptr[i]);
            printf("%2d\n", len_arr[index][i]);
        }
    }

    // free
    free_arr(len_arr, node_size);
    free_struct(node);
}
