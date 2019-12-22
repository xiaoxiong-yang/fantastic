#ifndef __PRI_QUEUE_H__
#define __PRI_QUEUE_H__

#include "huffman.h"

// 优先级队列的节点
typedef struct qNode {
	htNode *val; //  指向哈夫曼树的一个节点	
	unsigned short priority; // 优先级
	struct qNode *next;
}QueueNode;

typedef struct queue_ {
	QueueNode *first; // 队头指针
	int size; // 队列长度
}Queue;

// 初始化队列
void initQueue(Queue **queue);

// 往队列中装数据
void addQueue(Queue **queue, htNode *val, int priority);

// 从队列中取数据
htNode *getQueue(Queue **queue);

#endif //__PRI_QUEUE_H__

