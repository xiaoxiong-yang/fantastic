#include <stdio.h>
#include <stdlib.h>

#include "pri_queue.h"

// 初始化队列
void initQueue(Queue **queue){
	*queue = malloc(sizeof(Queue));
	(*queue)->first = NULL;
	(*queue)->size  = 0;
}

// 往队列中装数据
void addQueue(Queue **queue, htNode *val, int priority){
	QueueNode *p = malloc(sizeof(QueueNode));
	p->val = val;
	p->priority = priority;
	p->next = NULL;

	if ( (*queue)->first == NULL || (*queue)->size == 0 ) {
		(*queue)->first = p;
		(*queue)->size++;
		return;
	}
	
	if ( priority <= (*queue)->first->priority ) {
		p->next = (*queue)->first;
		(*queue)->first = p;
		(*queue)->size++;
		return;
	} else {
		QueueNode *cur = (*queue)->first;

		while ( cur->next != NULL ) {
			if ( priority <= cur->next->priority ) {
				p->next = cur->next;
				cur->next = p;
				(*queue)->size++;
				return;
			}	
			cur = cur->next;
		}

		if ( cur->next == NULL ) {
			p->next = NULL;
			cur->next = p;
			(*queue)->size++;
			return;
		}
	}
}

// 从队列中取数据
htNode *getQueue(Queue **queue){
	htNode *ret = NULL;

	if ( (*queue)->size > 0 ) {
		ret = (*queue)->first->val;
		(*queue)->first = (*queue)->first->next;
		(*queue)->size--;
	}

	return ret;
}

