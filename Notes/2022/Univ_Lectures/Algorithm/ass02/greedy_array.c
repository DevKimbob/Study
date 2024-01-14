#include "json.h"

int **len_arr;
int *D, *T;

extern int **parse_json(char *, node_name **, int *, int *);
extern void print_json(int **, int);
extern int get_node_index(node_name *, char *, int);
extern void free_arr(int **, int);
extern void free_struct(node_name *);

int get_small_index(int node_size) {
	int min = INF;
	int index = 0;

	for (int i = 0; i < node_size; i++) {
		if (D[i] < min && !T[i]) {
			min = D[i];
			index = i;
		}
	}

	return index;
}

void dijkstra(int start, int node_size) {
    int index;

	for (int i = 0; i < node_size; i++)
		D[i] = len_arr[start][i];
 
	T[start] = 1;
	for (int i = 0; i < node_size - 2; i++) {
		index = get_small_index(node_size);
		T[index] = 1;

		for (int j = 0; j < node_size; j++) {
            if (!T[j] && D[index] + len_arr[index][j] < D[j])
                D[j] = D[index] + len_arr[index][j];
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

    // set length array, confirmed
    D = (int *)malloc(sizeof(int) * node_size);
    T = (int *)malloc(sizeof(int) * node_size);
    for (int i = 0; i < node_size; i++) {
        D[i] = INF;
        T[i] = 0;
    }

    // greedy algorithm
    index = get_node_index(node, start, node_size);
    dijkstra(index, node_size);

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
    free(T);
    free_arr(len_arr, node_size);
    free_struct(node);
}