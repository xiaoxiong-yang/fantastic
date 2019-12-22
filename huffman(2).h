#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

// 哈夫曼树节点
typedef struct htNode_ {
	char symbol; // 装字符
	struct htNode_ *left;
	struct htNode_ *right;
}htNode;

// 哈夫曼树
typedef struct htTree_ {
	htNode *root;
}htTree;

// 哈夫曼编码表节点
typedef struct hlnode_ {
	char symbol; // 字符
	char *code;  // 字符对应的编码
	struct hlnode_ *next;
}hlNode;

// 哈夫曼编码链表
typedef struct hltable_ {
	hlNode *first;
	hlNode *last;
}hlTable;

// 构建哈夫曼树
htTree * buildTree(char *str);

// 通过哈夫曼树构建哈夫曼编码
hlTable *buildTable(htTree *huffmanTree);

// 编码
void encode(hlTable *table, char *strToEncode);

// 解码
void decode(htTree *tree, char *strToDecode);


#endif // __HUFFMAN_H__

