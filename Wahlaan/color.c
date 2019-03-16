#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {
	u32 v, n, c;
	map m = map_create(); G->x = 0;
	memset(G->color, -1, sizeof(G->color));
	fore(i, 0, G->n) {
		v = G->order[i]; c = 0;
		fore(j, 0, GradoDelVertice(G, v)) {
			n = NombreJotaesimoVecino(G, v, j);
			map_add(m, ColorDelVertice(G, j), ColorDelVertice(G, j));
		}
		while(map_find(m, c)) c++;
		G->x = max(G->x, c);
		G->color[v] = c;
		map_clear(m);
	}
}

int Bipartito(Grafo G) {
	int conflict = 0, c = 0;
	u32 v = G->order[0], neighbour;
	vector stack = vector_create();
	memset(G->color, -1, sizeof(G->color));
	vector_push_back(stack, v);
	G->color[v] = c; c++; G->x = 1;
	while(!vector_empty(stack)) {
		v = vector_pop_back(stack);
		fore(i, 0, GradoDelVertice(G, v)) {
			neighbour = NombreJotaesimoVecino(G, v, i);
			if(G->color[neighbour] != -1 && G->color[neighbour] != c)
				conflict = 1;
			if(!conflict) {
				vector_push_back(stack, neighbour);
				G->color[neighbour] = c;
			} else {
				Greedy(G);
				return 0;
			}
		}
		c = c == 1 ? 0 : 1;
	}
	G->x = 2;
	return !conflict;
}

#endif
