#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"

// the inline function to sort arrays length = 2
static inline void sort_2_num(int *pArr) {
	if (pArr[0] > pArr[1]) {
		int temp = pArr[0];
		pArr[0] = pArr[1];
		pArr[1] = temp;
	}
}

// write internal functions for quick_sort(), since it needs a random index
static void quick_sort_internal(int *pArr, int num) {
	int idx = rand() % num;
	int mid_val = pArr[idx];
	int i, j;

	if (num == 2) {
		sort_2_num(pArr);
		return;
	}

	i = 0;
	j = num-1;
	pArr[idx] = pArr[j];
	while(1) {
		while(i < j && pArr[i] <= mid_val) {
			i ++;
		}

		if (i != j) {
			pArr[j] = pArr[i];
		} else {
			break;
		}

		j --;
		while(j > i && pArr[j] >= mid_val) {
			j --;
		}

		if (j != i) {
			pArr[i] = pArr[j];
		} else {
			break;
		}

		i++;
	}

	if (i != j) { // can use assert()
		printf("Error: %s: after separate larger&smaller, i should be equal to j\n", __FUNCTION__);
		return;
	}
	pArr[i] = mid_val;

	if (i > 1) {
		quick_sort_internal(pArr, i);
	}

	if (i < num -2) {
		pArr += i+1;
		quick_sort_internal(pArr, num - i - 1);
	}
}

int quick_sort(int *pArr, int num) {
	if (pArr == NULL || num <= 1) {
		printf("Error: Bad arguments\n");
		return -1;
	}

	srand(time(NULL));
	quick_sort_internal(pArr, num);

	return 0;
}

