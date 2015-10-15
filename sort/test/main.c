#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common.h"
#include "sort.h"

#define NUM 10
#define COL 16

void print_arr(int *pArr, int num) {
	int i;

	for (i = 0; i < num/COL; i++) {
		int j;
		for (j = 0; j < COL; j++) {
			printf("%8d ", *pArr++);
		}
		printf("\n");
	}

	for (i = 0; i < num%COL; i++) {
		printf("%8d ", *pArr++);
	}

	if (num % COL) {
		printf("\n");
	}
}

int main() {
	int init_arr[NUM];
	int out_arr[NUM];
	int i;
	int ret;

	srand(time(NULL));
	for (i = 0; i < NUM; i++) {
		init_arr[i] = rand()%NUM;
	}

	//print_arr(init_arr, sizeof(init_arr)/sizeof(init_arr[0]));
	memcpy(out_arr, init_arr, sizeof(init_arr));
	printf("0. the original array is:\n");
	print_arr(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n1. test quick sort\n");
	TIME_CALL(ret, quick_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	printf("after sorting, the array is:\n");
	print_arr(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n2. test insert sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, insert_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	printf("after sorting, the array is:\n");
	print_arr(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n3. test bubble sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, bubble_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	printf("after sorting, the array is:\n");
	print_arr(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	printf("\n4. test heap sort\n");
	memcpy(out_arr, init_arr, sizeof(init_arr));
	TIME_CALL(ret, heap_sort(out_arr, sizeof(out_arr)/sizeof(out_arr[0])));
	printf("after sorting, the array is:\n");
	print_arr(out_arr, sizeof(out_arr)/sizeof(out_arr[0]));

	return 0;
}
