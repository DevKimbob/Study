#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "constdef.h"

// #define RAND_MAX  // same as INT_MAX = 2,147,483,647

int main() {
    int i, j, size, data;
    FILE *fp;
    char *data_dir = "src/";
    char *random[] = {"random.txt"};
    char *other[] = {"reverse.txt", "somerandom.txt", "first_one_tenth.txt", "last_one_tenth.txt"};
    char file[512];
    char buf[INT_LENGTH];

    srand((unsigned)time(NULL));

    // random
    size = sizeof(random) / sizeof(random[0]);
    for (i = 0; i < size; i++) {
        strcpy(file, data_dir);
        strcat(file, random[i]);
        fp = fopen(file, "w");

        for (j = 0; j < DATA_CNT; j++) {
            data = rand();
            fprintf(fp, "%d ", data);
        }

        fclose(fp);
    }

    // other
    size = sizeof(other) / sizeof(other[0]);
    for (i = 0; i < size; i++) {
        strcpy(file, data_dir);
        strcat(file, other[i]);
        fp = fopen(file, "w");

        switch (i) {
            case 0:  // reverse.txt
                for (j = 0; j < DATA_CNT; j++) {
                    fprintf(fp, "%d ", DATA_CNT - j);
                }
                break;
            case 1:  // somerandom.txt
                for (j = 1; j <= DATA_CNT; j++) {
                    if ((rand() % 100) == 1) {
                        fprintf(fp, "%d ", rand());
                    }
                    else
                        fprintf(fp, "%d ", j);
                }
                break;
            case 2:  // first_one_tenth.txt
                for (j = 1; j <= DATA_CNT / 10; j++) {
                    fprintf(fp, "%d ", rand());
                }
                for (; j <= DATA_CNT; j++) {
                    fprintf(fp, "%d ", j);
                }
                break;
            case 3:  // last_one_tenth.txt
                for (j = 1; j <= DATA_CNT * 9 / 10; j++) {
                    fprintf(fp, "%d ", j);
                }
                for (; j <= DATA_CNT; j++) {
                    fprintf(fp, "%d ", rand());
                }
                break;
        }
        fclose(fp);
    }

    puts("Completed");
}