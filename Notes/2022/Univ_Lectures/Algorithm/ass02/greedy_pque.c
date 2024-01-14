#include "json.h"
#include "heap.h"

int **len_arr;
int *D;

extern int **parse_json(char *, node_name **, int *, int *);
extern void print_json(int **, int);
extern int get_node_index(node_name *, char *, int);
extern void free_arr(int **, int);
extern void free_struct(node_name *);

void greedy_pque(int start, int node_size) {
    heap h;
    node n, poped;
    int cost, index, dist;

    init(&h);
    n.cost = 0;
    n.index = start;
    push(&h, n);
    D[start] = 0;

    while (h.datalen) {
        poped = pop(&h);
        cost = poped.cost;
        index = poped.index;

        if (D[index] < cost)
            continue;

        for (int i = 0; i < node_size; i++) {
            dist = len_arr[index][i] + cost;

            if (1 && (dist < D[i])) {
                D[i] = dist;
                n.cost = dist;
                n.index = i;
                push(&h, n);
            }
        }
    }

    deconst(&h);
}

int main() {
    char *filename = "./path.json";
    char *start = "Seoul";
    int node_size, m_size, index, min;
    node_name *node;

    // read and parse json file
    len_arr = parse_json(filename, &node, &node_size, &m_size);
    puts("== Graph of the given nodes ==");
    print_json(len_arr, node_size);
    puts("");

    // set length array, confirmed
    D = (int *)malloc(sizeof(int) * (node_size + 1));
    for (int i = 0; i < node_size + 1; i++)
        D[i] = INF;

    // greedy algorithm
    index = get_node_index(node, start, node_size);
    greedy_pque(index, node_size);

    // result
    printf("== Distances from %s : array D ==\n", start);
    for (int i = 0; i < node_size; i++)
        printf("%2d ", D[i]);
    puts("\n");

    printf("== Distances from %s : list ==\n", start);
    for (int i = 0; i < node_size; i++) {
        if (i != index) {
            printf("%s : ", node->node_ptr[i]);
            printf("%2d\n", D[i]);
        }
    }

    // free
    free(D);

    printf("\n== Graph after greedy algorithm ==\n");
    print_json(len_arr, node_size);

    free_arr(len_arr, node_size);  // segmentation fault
    free_struct(node);
}