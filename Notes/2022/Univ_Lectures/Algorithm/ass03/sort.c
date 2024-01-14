#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "constdef.h"

char *random_txt[] = {"random.txt"};
char *other[] = {"reverse.txt", "somerandom.txt", "first_one_tenth.txt", "last_one_tenth.txt"};
char *func[] = {"selection", "bubble", "bubble_noflag", "insert"};

void selection(int *data_array, int start, int end);
void bubble(int *data_array, int start, int end);
void bubble_noflag(int *data_array, int start, int end);
void insert(int *data_array, int start, int end);
int readtxt(int *data_array, int pos);
int writetxt(int *data_array, int pos);
int power(int base, int power);

int main(int argc, char *argv[]) {
    int *data_array;
    int i, j, k;
    clock_t start, end;
    void (*fp[4])(int *, int, int);
    int verbose = 0, option = 0;

    if ((argc > 1) && (strcmp(argv[1], "verbose") == 0)) {
        verbose = 1;

        for (i = 2; i < argc; i++) {
            option += power(2, atoi(argv[i]) - 1);
        }
    }

    fp[0] = selection;
    fp[1] = bubble;
    fp[2] = bubble_noflag;
    fp[3] = insert;

    data_array = (int *)malloc(sizeof(int) * DATA_CNT);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            readtxt(data_array, j);

            start = clock();
            fp[i](data_array, 0, DATA_CNT - 1);
            end = clock();
            printf("Function used : %s\n", func[i]);
            printf("Time spent : %lfs\n", (double)(end - start) / CLOCKS_PER_SEC);
            // printf("Time spent : %lfs (%ld clocks)\n", (double)(end - start) / CLOCKS_PER_SEC, end - start);

            writetxt(data_array, j);
            if (verbose && (option & power(2, j))) {
                for (k = 1; k <= 10; k++) {
                    printf("%6dth data : %12d\n", DATA_CNT / 10 * k, data_array[DATA_CNT / 10 * k - 1]);
                }
            }
            puts("");
        }
    }

    free(data_array);
}

void selection(int *data_array, int start, int end) {
    int temp, min;

    for (int i = 0; i < DATA_CNT - 1; i++) {
        min = i;

        for (int j = i + 1; j < DATA_CNT; j++) {
            if (data_array[j] < data_array[min])
                min = j;
        }

        temp = data_array[i];
        data_array[i] = data_array[min];
        data_array[min] = temp;
    }
}

void bubble(int *data_array, int start, int end) {
    int temp, flag;

    for (int i = 0; i < DATA_CNT - 1; i++) {
        flag = 0;

        for (int j = 0; j < DATA_CNT - i - 1; j++) {
            if (data_array[j] > data_array[j + 1]) {
                temp = data_array[j];
                data_array[j] = data_array[j + 1];
                data_array[j + 1] = temp;
                flag = 1;
            }
        }
        
        if (flag == 0)
            break;
    }
}

void bubble_noflag(int *data_array, int start, int end) {
    int temp;

    for (int i = 0; i < DATA_CNT - 1; i++) {
        for (int j = 0; j < DATA_CNT - i - 1; j++) {
            if (data_array[j] > data_array[j + 1]) {
                temp = data_array[j];
                data_array[j] = data_array[j + 1];
                data_array[j + 1] = temp;
            }
        }
    }
}

void insert(int *data_array, int start, int end) {
    int cur, j;

    for (int i = 1; i < DATA_CNT; i++) {
        cur = data_array[i];
        j = i - 1;
        while ((j >= 0) && (data_array[j] > cur)) {
            data_array[j + 1] = data_array[j];
            j--;
        }
        data_array[j + 1] = cur;
    }
}

int readtxt(int *data_array, int pos) {
    int i, j, size, data;
    FILE *fp;
    char *data_dir = "src/";
    char file[512];
    char buf[INT_LENGTH];

    size = sizeof(random_txt) / sizeof(random_txt[0]);
    strcpy(file, data_dir);
    if (size > pos) {
        strcat(file, random_txt[pos]);
    }
    else {
        strcat(file, other[pos - size]);
    }

    fp = fopen(file, "r");
    for (i = 0; i < DATA_CNT; i++) {
        fscanf(fp, "%d ", &data);
        *(data_array + i) = data;
    }
}

int writetxt(int *data_array, int pos) {
    int i, j, size, data;
    FILE *fp;
    char *data_dir = "dst/";
    char file[512];
    char buf[INT_LENGTH];

    size = sizeof(random_txt) / sizeof(random_txt[0]);
    strcpy(file, data_dir);
    if (size > pos) {
        strcat(file, random_txt[pos]);
        printf("Dataset : %s\n", random_txt[pos]);
    }
    else {
        strcat(file, other[pos - size]);
        printf("Dataset : %s\n", other[pos - size]);
    }

    fp = fopen(file, "w");
    for (i = 0; i < DATA_CNT; i++) {
        fprintf(fp, "%d ", *(data_array + i));
    }
}

int power(int base, int power) {
    int result = 1;

    for (int i = 0; i < power; i++)
        result *= base;
    
    return result;
}