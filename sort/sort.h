#ifndef _SORT_H
#define _SORT_H

#include "common.h"

// unstable sort、In-place sort, O(nlogn)
int quick_sort(TDataType *pArr, int num);
//int merge_sort(int *pArr, int num);
// stable sort、In-place sort, O(n^2)
int insert_sort(TDataType *pArr, int num);
// stable sort、In-place sort, O(n^2)
int bubble_sort(TDataType *pArr, int num);
// unstable sort、In-place sort, O(nlogn)
int heap_sort(TDataType *pArr, int num);
// In-place sort，unstable sort, O(n^2)
int select_sort(TDataType *pArr, int num);
// stable sort、out-place sort, O(n+k)
// need to know the max of the value in array and all values are positive
int count_sort(TDataType *pArr, int num, int max);

#endif // _SORT_H
