#include "bstree.h"
#include <stdio.h>

int main(){
	map m = map_create();
	for(int i = 10000000; i >= 0; i--) {
		map_add(m, i, i);
	}
	printf("%d\n", m->root->height);
	return 0;
}