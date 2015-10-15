#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"

#define SWAP_INT(a, b) do {a = a ^ b; b = a ^ b; a = a ^ b;} while(0)
#define CHECK_ARGS() \
	if (pArr == NULL || num <= 1) {			\
		TMP_LOGE("Bad arguments\n");	\
		return -1;				\
	}						\
							\
	if (num == 2) {					\
		sort_2_num(pArr);			\
		return 0;				\
	}


// the inline function to sort arrays length = 2
static inline void sort_2_num(int *pArr) {
	if (pArr[0] > pArr[1]) {
		SWAP_INT(pArr[0], pArr[1]);
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
		TMP_LOGE("after separate larger&smaller, i should be equal to j\n");
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
	CHECK_ARGS();

	srand(time(NULL));
	quick_sort_internal(pArr, num);

	return 0;
}

int insert_sort(int *pArr, int num) {
	int i;

	CHECK_ARGS();

	for (i = 1; i < num; i++) {
		int j = i;
		int val=pArr[i];
		while(j > 0) {
			if (pArr[j-1] > val) {
				pArr[j] = pArr[j-1];
				j--;
			} else {
				pArr[j] = val;
				break;
			}
		}

		if (j == 0) {
			pArr[0] = val;
		}
	}
	return 0;
}

int bubble_sort(int *pArr, int num) {
	int i,j;

	CHECK_ARGS();

	j = num - 1;
	do {
		for(i = 0; i < j; i++) {
			if (pArr[i] > pArr[i+1]) {
				SWAP_INT(pArr[i], pArr[i+1]);
			}
		}
	} while(--j > 0);

	return 0;
}

////////////////heap related op//////////////////
#define LEFT_LEAF(n) (2*(n)+1)
#define RIGHT_LEAF(n) (2*(n)+2)
extern void print_arr(int *pArr, int num);
static void large_heap_adjust(int *, int, int);

static void large_heap_create(int *pArr, int head, int num) {
	if (head + 1 >= num) {
		return;
	}

	if (RIGHT_LEAF(head) < num) {
		large_heap_create(pArr, LEFT_LEAF(head), num);
		large_heap_create(pArr, RIGHT_LEAF(head), num);
		large_heap_adjust(pArr, head, num);

	} else if (LEFT_LEAF(head) < num) {
		if (pArr[head] < pArr[LEFT_LEAF(head)]) {
			SWAP_INT(pArr[head], pArr[LEFT_LEAF(head)]);
		}
	}
}

static void large_heap_adjust(int *pArr, int head, int num) {
	if (head + 1 >= num) {
		return;
	}

	if (RIGHT_LEAF(head) < num) {
		if (pArr[LEFT_LEAF(head)] > pArr[RIGHT_LEAF(head)]) {
			if (pArr[head] < pArr[LEFT_LEAF(head)]) {
				SWAP_INT(pArr[head], pArr[LEFT_LEAF(head)]);
				large_heap_adjust(pArr, LEFT_LEAF(head), num);
			}

		} else {
			if (pArr[head] < pArr[RIGHT_LEAF(head)]) {
				SWAP_INT(pArr[head], pArr[RIGHT_LEAF(head)]);
				large_heap_adjust(pArr, RIGHT_LEAF(head), num);
			}

		}
	} else if (LEFT_LEAF(head) < num) {
		if (pArr[head] < pArr[LEFT_LEAF(head)]) {
			SWAP_INT(pArr[head], pArr[LEFT_LEAF(head)]);
		}
	}
}

int heap_sort(int *pArr, int num) {
	CHECK_ARGS();

	large_heap_create(pArr, 0, num);
	TMP_LOGV("atfer creating heap\n");
	printf_arr_verbose(pArr, num);
	TMP_LOGV("adjusting heap\n");
	SWAP_INT(pArr[0], pArr[num-1]);
	while(--num > 1) {
		large_heap_adjust(pArr, 0, num);
		printf_arr_verbose(pArr, num);
		SWAP_INT(pArr[0], pArr[num-1]);
	}

	return 0;
}

int select_sort(int *pArr, int num) {
	CHECK_ARGS();

	do {
		int i;
		int max_val_idx = 0;

		for (i = 1; i < num; i++) {
			if (pArr[i] >= pArr[max_val_idx]) {
				max_val_idx = i;
			}
		}

		TMP_LOGV("the max value is the %d one %d\n", max_val_idx, pArr[max_val_idx]);
		if(pArr[num-1] != pArr[max_val_idx]) {
			SWAP_INT(pArr[num-1], pArr[max_val_idx]);
		}
		printf_arr_verbose(pArr, num);
	} while(--num > 1);

	return 0;
}

int count_sort(int *pArr, int num, int max) {
	int i, j;
	int *cnt_array = NULL;
	CHECK_ARGS();

	if (max < 0) {
		TMP_LOGE("max value is negtive!\n");
		return -1;
	}

	i = num - 1;
	do {
		if (pArr[i] < 0) {
			TMP_LOGE("max value is negtive!\n");
			return -1;
		}
	} while(--i >= 0);

	cnt_array = (int *)malloc((max + 1) * sizeof(int));
	if (!cnt_array) {
		TMP_LOGE("allocate count array failed!\n");
		return -1;
	}

	memset(cnt_array, 0, (max + 1) * sizeof(int));
	i = num - 1;
	do {
		cnt_array[pArr[i]]++;
	} while (--i >= 0);

	for(i = 1; i < max+1; i++) {
		cnt_array[i] += cnt_array[i-1];
	}

	i = 0;
	j = 0;
	do {
		while(i < cnt_array[j]) {
			pArr[i++] = j;
		}
		j++;
	} while(i < num && j < max + 1);
	free(cnt_array);
	return 0;
}