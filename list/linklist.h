#ifndef _LINK_LIST_H
#define _LINK_LIST_H

#include <stdlib.h>
#include "common.h"

// Note:
//	1. pHeader to point to an empty node, to keep operation coherence
typedef struct _S_Node {
	TDataType val;
	struct _S_Node *pNext;
} s_Node, *ps_Node;

// function: link_list_init()
// description: init a new list, actually, it will allocate
//		an empty node, and return the pointer to it.
// return: the pointer to the header Node. NULL if failed.
s_Node *link_list_init();

// function: link_list_destroy()
// description: free every node of the list
// arguments:
//	pHead: the header pointer. Nothing will happen if it's NULL
// return:
//	the header pointer, it should be NULL
s_Node *link_list_destroy(s_Node *pHead);

// function: link_list_append()
// description: append a node to the tail
// arguments:
//	pHead: the header pointer, can't be NULL
//	item: the content of new node
// return:
//	0: sucess; -1: failed
int link_list_append(s_Node *pHead, TDataType *item);

// function: link_list_insert()
// description: insert a node to the list
// arguments:
//	pHead: the header pointer, can't be NULL
//	item: the content of new node
//	index: the position of the new node (count from 0)
// return:
//	0: sucess; -1: failed
int link_list_insert(s_Node *pHead, TDataType *item, int index);

// function: link_list_sorted_insert()
// description: similar to link_list_insert, but keep the link list sorted
int link_list_sorted_insert(s_Node *pHead, TDataType *item);

// function: link_list_delete()
// description: delete a node to the list
// arguments:
//	pHead: the header pointer, can't be NULL
//	index: the position of the node to del (count from 0)
// return:
//	0: sucess; -1: failed
int link_list_delete(s_Node *pHead, int index);

// function: link_list_search()
// description: search  the list and return the index of the 1st node
//		that has the same content of item
// arguments:
//	pHead: the header pointer, can't be NULL
//	item: the content to be searched
// return:
//	(< 0): the content can't be found
//	others: the index of the node
int link_list_search(s_Node *pHead, TDataType *item);

// function: link_list_length()
// description: return the length the list
// arguments:
//	pHead: the header pointer, can't be NULL
// return:
//	the length of the list
int link_list_length(s_Node *pHead);

int print_list(s_Node *pHead);

#endif // _LINK_LIST_H
