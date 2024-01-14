#include <iostream>
#include <stdio.h>

int main() {
    static int nSource[4], nDest[4];
    static int bucket[2][10];
    int ap[2] = { 0, };
    int i, j, l, tmp, k = 4;
    int max, min;

    // input -> nSource
    nSource[0] = 4;
    nSource[1] = 7;
    nSource[2] = 9;
    nSource[3] = 2;

    // find max
    max = nSource[0];
	for (i = 1; i <= k - 1; i++) {
		if (nSource[i] > max)
			max = nSource[i];
	}

	// nSource -> buckets
	for (i = 0; i < k; i++) {
		if (nSource[i] > max / 2) {
			bucket[1][ap[1]++] = nSource[i];
		}
		else
			bucket[0][ap[0]++] = nSource[i];
	}

	// sort buckets : selection sort
	for (i = 0; i < 2; i++) {
		for (j = 0; j < ap[i]; j++) {
			min = j;
			for (l = j; l < ap[i]; l++) {
				if (bucket[i][l] < bucket[i][min])
					min = l;
			}
			tmp = bucket[i][min];
			bucket[i][min] = bucket[i][j];
			bucket[i][j] = tmp;
		}
	}

	// bucket -> nDest
	for (i = 0; i < ap[0]; i++) {
		nDest[i] = bucket[0][i];
	}
	for (j = 0; j < ap[1]; j++) {
		nDest[i + j] = bucket[1][j];
	}

    // print nDest
    for (i = 0; i < k; i++) {
        printf("%d ", nDest[i]);
    }
    puts("");
}