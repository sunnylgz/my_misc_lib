#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <sys/time.h>

#define TIME_CALL(ret, fun) \
    {                                                                   \
        struct timeval start_time, end_time;                            \
        long long elapse_us;                                            \
        gettimeofday(&start_time, NULL);                                \
        ret = fun;                                                      \
        gettimeofday(&end_time, NULL);                                  \
        elapse_us = (end_time.tv_sec * 1000000 + end_time.tv_usec)      \
            - (start_time.tv_sec * 1000000 + start_time.tv_usec);       \
        printf("time elapse: %lld s %lld us\n", elapse_us / 1000000,    \
                elapse_us % 1000000);                                   \
    }

// log system, use TMP_ as prefix to avoid conflict w/ others like Android source codes.
// LOGV is enabled when (_DEBUG > 1)
// LOGD is enabled when (_DEBUG > 0)
// LOGE/LOGI is always enabled
#define TMP_LOGI(str, ...) printf("[Info] %s: "str, __FUNCTION__, ##__VA_ARGS__)
#define TMP_LOGE(str, ...) printf("[Error] %s: "str, __FUNCTION__, ##__VA_ARGS__)
#define TMP_LOGD(str, ...) do { if(0) printf("[Debug] %s: "str, __FUNCTION__, ##__VA_ARGS__); } while(0)
#define TMP_LOGV(str, ...) do { if(0) printf("[Verbose] %s: "str, __FUNCTION__, ##__VA_ARGS__); } while(0)
#ifdef _DEBUG
  #define TMP_LOGD(str, ...) printf("[Debug] %s: "str, __FUNCTION__, ##__VA_ARGS__)

  #if _DEBUG > 1
    #define TMP_LOGV(str, ...) printf("[Verbose] %s: "str, __FUNCTION__, ##__VA_ARGS__)
  #endif
#endif // _DEBUG

// type & op related to data type
typedef int TDataType;

#define CMP_LT(x, y) ((x) < (y))
#define CMP_LE(x, y) ((x) <= (y))
#define CMP_GT(x, y) ((x) > (y))
#define CMP_GE(x, y) ((x) >= (y))
#define CMP_NE(x, y) ((x) != (y))
#define IS_POS(x) ((x) > 0)
#define IS_NEG(x) ((x) < 0)
#define EXTRACT_IDX(x) (x)				// extract the index of element that can be compared

#define SWAP_VAL(a, b) do {a = a ^ b; b = a ^ b; a = a ^ b;} while(0)

// debuging functions
#define COL 16	// print array as 16 elements a row
static void print_arr(TDataType *pArr, int num) {
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

static void fwrite_arr(const char *fname, TDataType *pArr, int num) {
	FILE *file_handle;
	int i;

	file_handle = fopen(fname, "w");
	if (!file_handle) {
		TMP_LOGE("open %s failed!\n", fname);
	}

	for (i = 0; i < num/COL; i++) {
		int j;
		for (j = 0; j < COL; j++) {
			fprintf(file_handle, "%8d ", *pArr++);
		}
		fprintf(file_handle, "\n");
	}

	for (i = 0; i < num%COL; i++) {
		fprintf(file_handle, "%8d ", *pArr++);
	}

	fclose(file_handle);
	TMP_LOGI("write array to %s\n", fname);
}

static inline void print_val(TDataType x) {
	printf("%8d", x);
}

#define printf_arr_debug(...)
#define printf_arr_verbose(...)
#ifdef _DEBUG
  #define printf_arr_debug(...) print_arr(__VA_ARGS__)

  #if _DEBUG > 1
    #define printf_arr_verbose(...) print_arr(__VA_ARGS__)
  #endif
#endif // _DEBUG

#endif // _COMMON_H
