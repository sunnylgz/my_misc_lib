#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common.h"
#include "sort.h"

#define NUM 1000

int main() {
	TDataType init_arr[NUM];
	TDataType out_arr[NUM];
	int i;
	int ret;

	srand(time(NULL));
	for (i = 0; i < NUM; i++) {
		init_arr[i] = rand()%NUM;
	}

	memcpy(out_arr, init_arr, sizeof(init_arr));
	TMP_LOGD("0. the original array is:\n");
	printf_arr_debug(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));
	fwrite_arr("init_arr.txt", out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n1. test quick sort\n");
	TIME_CALL(ret, quick_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	TMP_LOGD("after sorting, the array is:\n");
	printf_arr_debug(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));
	fwrite_arr("quick_sort.txt", out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n2. test insert sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, insert_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	TMP_LOGD("after sorting, the array is:\n");
	printf_arr_debug(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));
	fwrite_arr("insert_sort.txt", out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n3. test bubble sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, bubble_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	TMP_LOGD("after sorting, the array is:\n");
	printf_arr_debug(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));
	fwrite_arr("bubble_sort.txt", out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n4. test heap sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, heap_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	TMP_LOGD("after sorting, the array is:\n");
	printf_arr_debug(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));
	fwrite_arr("heap_sort.txt", out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n5. test select sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, select_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	TMP_LOGD("after sorting, the array is:\n");
	printf_arr_debug(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));
	fwrite_arr("select_sort.txt", out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n6. test count sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, count_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0]), NUM));
	TMP_LOGD("after sorting, the array is:\n");
	printf_arr_debug(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));
	fwrite_arr("count_sort.txt", out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	return 0;
}
