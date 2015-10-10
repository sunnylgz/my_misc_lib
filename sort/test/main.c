#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#define NUM 20
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
	int i;

	srand(time(NULL));
	for (i = 0; i < NUM; i++) {
		init_arr[i] = rand()%NUM;
	}

	print_arr(init_arr, sizeof(init_arr)/sizeof(init_arr[0]));

	return 0;
}
