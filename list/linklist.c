#include "linklist.h"

s_Node *link_list_init() {
	return (s_Node*)calloc(1, sizeof(s_Node));
}

s_Node *link_list_destroy(s_Node *pHead) {
	if(pHead == NULL) {
		TMP_LOGI("pHead is NULL!\n");
	} else {
		s_Node *pNode = pHead->pNext;
		while(pNode) {
			s_Node *pTemp = pNode;
			pNode = pNode->pNext;
			free(pTemp);
		}
		free(pHead);
		pHead = NULL;
	}

	return pHead;
}

int link_list_append(s_Node *pHead, TDataType *item) {
	if (pHead == NULL || item == NULL) {
		TMP_LOGE("Bad arguments!\n");
		return -1;
	}

	s_Node *pNew = (s_Node*)malloc(sizeof(s_Node));
	if (pNew == NULL) {
		TMP_LOGE("allocate new node failed!\n");
		return -1;
	}

	while (pHead->pNext) {
		pHead = pHead->pNext;
	}

	pNew->val = *item;
	pNew->pNext = NULL;
	pHead->pNext = pNew;

	return 0;
}

int link_list_insert(s_Node *pHead, TDataType *item, int index) {
	if (pHead == NULL || item == NULL) {
		TMP_LOGE("Bad arguments!\n");
		return -1;
	}


}

int print_list(s_Node *pHead) {
	int cnt;
	if (pHead == NULL) {
		TMP_LOGE("Bad arguments!\n");
		return -1;
	}

	while (pHead->pNext) {
		print_val(pHead->pNext->val);
		pHead = pHead->pNext;
		if (++cnt % COL) {
			printf("\n");
		}
	}

	return cnt;
}
