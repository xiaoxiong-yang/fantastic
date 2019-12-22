#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "pri_queue.h"

htTree * buildTree(char *str) {
	int proc[256] = {0};
	int i;

	// 统计每个字符使用的次数
	for (i=0; str[i]!=0; i++ ) {
		proc[str[i]]++;
	}
	
	// 构建优先级队列
	Queue *huffmanQueue;
	initQueue(&huffmanQueue);

	// 将所有节点都装入优先级队列
	for (i=0; i<256; i++) {
		if ( proc[i] > 0 ) {
			htNode *p = malloc(sizeof(htNode));
			p->symbol = (char)i;
			p->left = NULL;
			p->right = NULL;
			addQueue(&huffmanQueue, p, proc[i]);
		}
	}

	// 生成哈夫曼树
	while ( huffmanQueue->size > 1 ) {
		int pri = huffmanQueue->first->priority;
		pri += huffmanQueue->first->next->priority;

		htNode *first  = getQueue(&huffmanQueue);
		htNode *second = getQueue(&huffmanQueue);
		
		htNode *newNode = malloc(sizeof(htNode));
		newNode->left = first;
		newNode->right = second;

		addQueue(&huffmanQueue, newNode, pri);
	}

	htTree *tree = malloc(sizeof(htTree));
	tree->root = getQueue(&huffmanQueue);

	return tree;
}

// 根据哈夫曼树，生成哈夫曼编码，k指的是走的步数，code，记录向左还是向右
static void travelTree(htNode *treeNode, hlTable **table, 
					int k, char code[256]) {
	
	if ( treeNode->left==NULL && treeNode->right== NULL ) {
		code[k] = 0;
		hlNode * p = malloc(sizeof(hlNode));
		p->symbol = treeNode->symbol;
		p->code = malloc(strlen(code)+1);
		strcpy(p->code, code);
		p->next = NULL;
		
		if ( (*table)->first == NULL ) {
			(*table)->first = p;
			(*table)->last  = p;
		} else {
			(*table)->last->next  = p;
			(*table)->last = p;
		}
	}
	
	if ( treeNode->left != NULL ) {
		code[k] = '0';
		travelTree(treeNode->left, table, k+1, code); 
	}

	if ( treeNode->right != NULL ) {
		code[k] = '1';
		travelTree(treeNode->right, table, k+1, code); 
	}
}

// 通过哈夫曼树构建哈夫曼编码
hlTable *buildTable(htTree *huffmanTree) {
	hlTable *table = malloc(sizeof(hlTable));
	table->first = NULL;
	table->last  = NULL;
	
	int k = 0;
	char code[256];
	travelTree(huffmanTree->root, &table, k, code);

	return table;
}

// 编码
void encode(hlTable *table, char *strToEncode) {
	int i;
	
	for (i=0; strToEncode[i]!=0; i++) {
		hlNode *cur = table->first;
		
		while ( cur != NULL ) {
			if ( cur->symbol == strToEncode[i] ) {
				printf("%s", cur->code);
				break;
			}	
			cur = cur->next;
		}
	}
	printf("\n");
}

// 解码
void decode(htTree *tree, char *strToDecode) {
	htNode *cur = tree->root;
	int i;
	for (i=0; strToDecode[i]!=0; i++) {
		if ( cur->left==NULL && cur->right==NULL ) {
			printf("%c", cur->symbol);
			cur = tree->root;
		}

		if ( strToDecode[i] == '1' ) {
			cur = cur->right;
		}
		if ( strToDecode[i] == '0' ) {
			cur = cur->left;
		}

		if ( strToDecode[i]!='0' && strToDecode[i]!='1') {
			printf("编码错误\n");
			return;
		}
	}
	if ( cur->left==NULL && cur->right==NULL ) {
		printf("%c", cur->symbol);
		cur = tree->root;
	}

	printf("\n");
}

