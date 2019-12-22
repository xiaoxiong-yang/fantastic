#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#include "pri_queue.h"

int main( void ) {
	htTree *tree = buildTree("alyyyiobabatentxunmimibaiduhuawei");
	hlTable *codeTable = buildTable(tree);
	
	hlNode *cur = codeTable->first;
	
	while ( cur != NULL ) {
		printf("%c : %s\n", cur->symbol, cur->code);
		cur = cur->next;
	}

	encode(codeTable);
	decode(tree);
}

