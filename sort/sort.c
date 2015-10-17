#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"

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
static inline void sort_2_num(TDataType *pArr) {
	if (CMP_GT(pArr[0], pArr[1])) {
		SWAP_VAL(pArr[0], pArr[1]);
	}
}

// write internal functions for quick_sort(), since it needs a random index
static void quick_sort_internal(TDataType *pArr, int num) {
	int idx = rand() % num;
	TDataType mid_val = pArr[idx];
	int i, j;

	if (num == 2) {
		sort_2_num(pArr);
		return;
	}

	i = 0;
	j = num-1;
	pArr[idx] = pArr[j];
	while(1) {
		while(i < j && CMP_LE(pArr[i], mid_val)) {
			i ++;
		}

		if (i != j) {
			pArr[j] = pArr[i];
		} else {
			break;
		}

		j --;
		while(j > i && CMP_GE(pArr[j], mid_val)) {
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

int quick_sort(TDataType *pArr, int num) {
	CHECK_ARGS();

	srand(time(NULL));
	quick_sort_internal(pArr, num);

	return 0;
}

int insert_sort(TDataType *pArr, int num) {
	int i;

	CHECK_ARGS();

	for (i = 1; i < num; i++) {
		int j = i;
		TDataType val=pArr[i];
		while(j > 0) {
			if (CMP_GT(pArr[j-1], val)) {
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

int bubble_sort(TDataType *pArr, int num) {
	int i,j;

	CHECK_ARGS();

	j = num - 1;
	do {
		for(i = 0; i < j; i++) {
			if (CMP_GT(pArr[i], pArr[i+1])) {
				SWAP_VAL(pArr[i], pArr[i+1]);
			}
		}
	} while(--j > 0);

	return 0;
}

////////////////heap related op//////////////////
#define LEFT_LEAF(n) (2*(n)+1)
#define RIGHT_LEAF(n) (2*(n)+2)
static void large_heap_adjust(TDataType *, int, int);

static void large_heap_create(TDataType *pArr, int head, int num) {
	if (head + 1 >= num) {
		return;
	}

	if (RIGHT_LEAF(head) < num) {
		large_heap_create(pArr, LEFT_LEAF(head), num);
		large_heap_create(pArr, RIGHT_LEAF(head), num);
		large_heap_adjust(pArr, head, num);

	} else if (LEFT_LEAF(head) < num) {
		if (CMP_LT(pArr[head], pArr[LEFT_LEAF(head)])) {
			SWAP_VAL(pArr[head], pArr[LEFT_LEAF(head)]);
		}
	}
}

static void large_heap_adjust(TDataType *pArr, int head, int num) {
	if (head + 1 >= num) {
		return;
	}

	if (RIGHT_LEAF(head) < num) {
		if (CMP_GT(pArr[LEFT_LEAF(head)], pArr[RIGHT_LEAF(head)])) {
			if (CMP_LT(pArr[head], pArr[LEFT_LEAF(head)])) {
				SWAP_VAL(pArr[head], pArr[LEFT_LEAF(head)]);
				large_heap_adjust(pArr, LEFT_LEAF(head), num);
			}

		} else {
			if (CMP_LT(pArr[head], pArr[RIGHT_LEAF(head)])) {
				SWAP_VAL(pArr[head], pArr[RIGHT_LEAF(head)]);
				large_heap_adjust(pArr, RIGHT_LEAF(head), num);
			}

		}
	} else if (LEFT_LEAF(head) < num) {
		if (CMP_LT(pArr[head], pArr[LEFT_LEAF(head)])) {
			SWAP_VAL(pArr[head], pArr[LEFT_LEAF(head)]);
		}
	}
}

int heap_sort(TDataType *pArr, int num) {
	CHECK_ARGS();

	large_heap_create(pArr, 0, num);
	TMP_LOGV("atfer creating heap\n");
	printf_arr_verbose(pArr, num);
	TMP_LOGV("adjusting heap\n");
	SWAP_VAL(pArr[0], pArr[num-1]);
	while(--num > 1) {
		large_heap_adjust(pArr, 0, num);
		printf_arr_verbose(pArr, num);
		SWAP_VAL(pArr[0], pArr[num-1]);
	}

	return 0;
}

int select_sort(TDataType *pArr, int num) {
	CHECK_ARGS();

	do {
		int i;
		int max_val_idx = 0;

		for (i = 1; i < num; i++) {
			if (CMP_GE(pArr[i], pArr[max_val_idx])) {
				max_val_idx = i;
			}
		}

		TMP_LOGV("the max value is the %d one %d\n", max_val_idx, pArr[max_val_idx]);
		if(CMP_NE(pArr[num-1], pArr[max_val_idx])) {
			SWAP_VAL(pArr[num-1], pArr[max_val_idx]);
		}
		printf_arr_verbose(pArr, num);
	} while(--num > 1);

	return 0;
}

// will record the count of each items and save the values to list array,
// and then output the lists to the original array according to the count.
int count_sort(TDataType *pArr, int num, int max) {
	typedef struct _S {
		TDataType val;
		struct _S *pNext;
	} s_listNode, *ps_listNode;

	int i, j;
	int ret = 0;
	int *cnt_array = NULL;
	s_listNode *item_array = NULL; // save the items to a list array, coresponding to count array
	CHECK_ARGS();

	if (max < 0) {
		TMP_LOGE("max value is negtive!\n");
		return -1;
	}

	i = num - 1;
	do {
		if (IS_NEG(pArr[i])) {
			TMP_LOGE("max value is negtive!\n");
			return -1;
		}
	} while(--i >= 0);

	cnt_array = (int *)malloc((max + 1) * sizeof(int));
	item_array = (s_listNode*)malloc((max + 1) * sizeof(*item_array));
	if (!cnt_array || !item_array) {
		TMP_LOGE("allocate count array failed!\n");
		ret = -1;
		goto _return_cleanup;
	}

	memset(cnt_array, 0, (max + 1) * sizeof(int));
	memset(item_array, 0, (max + 1) * sizeof(*item_array));
	i = num - 1;
	do {
		ps_listNode pHead;
		cnt_array[EXTRACT_IDX(pArr[i])]++;
		pHead = &item_array[EXTRACT_IDX(pArr[i])];

		while (pHead->pNext) {
			pHead = pHead->pNext;
		}
		pHead->pNext = (ps_listNode)malloc(sizeof(*pHead));
		pHead = pHead->pNext;
		TMP_LOGD("allocate a node: %p\n", pHead);
		if (!pHead) {
			TMP_LOGE("allocate item list node failed!\n");
			ret = -1;
			goto _return_cleanup;
		}
		pHead->val = pArr[i];
		pHead->pNext = NULL;
	} while (--i >= 0);

	for(i = 1; i < max+1; i++) {
		cnt_array[i] += cnt_array[i-1];
	}

	i = 0;
	j = 0;
	do {
		ps_listNode pHead = item_array[j].pNext;
		while(i < cnt_array[j] && pHead) {
			ps_listNode pTempHead = pHead;
			pArr[i++] = pHead->val;
			pHead = pHead->pNext;
		}
		j++;
	} while(i < num && j < max + 1);

_return_cleanup:
	if(item_array) {
		for (i = 0; i < max + 1; i++) {
			ps_listNode pHead = item_array[i].pNext;
			while(pHead) {
				ps_listNode pTempHead = pHead;
				pHead = pHead->pNext;
				TMP_LOGD("free a node: %p\n", pTempHead);
				free(pTempHead);
			}
		}
	}
	free(cnt_array);
	free(item_array);
	return ret;
}