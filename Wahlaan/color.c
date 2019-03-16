#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {
	memset(G->color, -1, sizeof(G->color));

	map m = map_create(); G->x = 0;
	fore(i, 0, G->n) {
		u32 v = G->order[i], c = 0;
		fore(j, 0, GradoDelVertice(G, v)) {
			u32 n = NombreJotaesimoVecino(G, v, j);
			map_add(m, ColorDelVertice(G, j), ColorDelVertice(G, j));
		}
		while(map_find(m, c)) c++;
		G->x = (c > G->x) ? c : G->x;
		G->color[v] = c;
		map_clear(m);
	}
}

int Bipartito(Grafo G) {
	memset(G->color, -1, sizeof(G->color));
	vector stack = vector_create();

	u32 v = G->order[0];
	vector_push_back(stack, v);
	G->color[v] = 0; G->x = 2;

	while(!vector_empty(stack)) {
		v = vector_pop_back(stack);
		fore(i, 0, GradoDelVertice(G, v)) {
			u32 n = NombreJotaesimoVecino(G, v, i);
			if(G->color[n] == G->color[v]) {
				Greedy(G);
				return 0;
			}
			if(G->color[n] == -1) G->color[n] = (G->color[v] + 1) % 2, vector_push_back(stack, n);
		}
	}
	return 1;
}

#endif
