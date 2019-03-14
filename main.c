#include "map.h"

int main(){
	map m = map_create();
	for(int i = 10000000; i >= 0; i--) {
		map_add(m, i, i);
	}
	return 0;
}