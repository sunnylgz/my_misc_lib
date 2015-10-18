#include <stdio.h>
#include <time.h>
#include "common.h"
#include "linklist.h"

int main(int argc, char *argv[]) {
	s_Node *pList = link_list_init();
	s_Node *pSortedList = link_list_init();
	int len = 10;
	int i;

	if (argc > 1) {
		len = atoi(argv[1]);
	}
	TMP_LOGD("the specified length of list is %d\n", len);
	srand(time(NULL));

	for (i = 0; i < len; i++) {
		int val = rand()%len;
		if (link_list_append(pList, &val)) {
			TMP_LOGE("call link_list_init() failed!\n");
		}
		if (link_list_sorted_insert(pList, &val)) {
			TMP_LOGE("call link_list_sorted_insert() failed!\n");
		}
	}

_return:
	link_list_destroy(pList);
	link_list_destroy(pSortedList);
	return 0;
}