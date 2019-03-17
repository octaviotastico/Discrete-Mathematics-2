#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {
	memset(G->color, ~0u, G->n * sizeof(u32));

	map m = map_create(); G->x = 0;

	if(!m) return 1;

	fore(i, 0, G->n) {
		printf("BEGIN\n");
		u32 v = G->order[i], c = 0;
		fore(j, 0, GradoDelVertice(G, i)) {
			u32 x = ColorJotaesimoVecino(G, i, j);
			if(x != ~0u) if(map_add(m, x, 0)) return 1;
		}
		while(map_find(m, c)) c++;
		G->color[v] = c;
		G->x = max(G->x, c + 1);
		map_clear(m);
		printf("END\n");
	}
	map_destroy(m);
	return 0;
}

int Bipartito(Grafo G) {
	memset(G->color, -1, G->n * sizeof(u32));
	vector stack = vector_create();

	u32 v = G->order[0];
	vector_push_back(stack, v);
	G->color[v] = 0; G->x = 2;

	while(!vector_empty(stack)) {
		v = vector_pop_back(stack);
		fore(i, 0, GradoDelVertice(G, v)) {
			u32 n = vector_at(G->g[v], i);
			if(G->color[n] == G->color[v]) {
				vector_destroy(stack);
				Greedy(G);
				return 0;
			}
			if(G->color[n] == ~0u) {
				G->color[n] = (G->color[v] + 1) % 2;
				vector_push_back(stack, n);
			}
		}
	}
	vector_destroy(stack);
	return 1;
}

#endif
