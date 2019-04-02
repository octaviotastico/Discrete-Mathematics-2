#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {
	u32* available = calloc(G->n, sizeof(u32));
	vector v = vector_create();

	if(!available || !v) return 1;

	memset(G->color, ~0u, G->n * sizeof(u32));

	G->x = 0;

	fore(i, 0, G->n) {
		fore(j, 0, GradoDelVertice(G, i)) {
			u32 x = ColorJotaesimoVecino(G, i, j);
			if(x != ~0u && !available[x]) {
				available[x] = 1;
				if(vector_push_back(v, x)) {
					free(available);
					return 1;
				}
			}
		}
		u32 c = 0;
		while(available[c]) c++;
		G->color[G->order[i]] = c;
		G->x = max(G->x, c + 1);
		while(!vector_empty(v)) available[vector_pop_back(v)] = 0;
	}
	free(available);
	vector_destroy(v);
	return 0;
}

int Bipartito(Grafo G) {
	memset(G->color, ~0u, G->n * sizeof(u32));
	vector stack = vector_create();

	G->x = 1;

	fore(i, 0, G-> n) if(G->color[i] == ~0u) {
		vector_push_back(stack, i);
		G->color[i] = 0;
		while(!vector_empty(stack)) {
			u32 v = vector_pop_back(stack);
			fore(j, 0, vector_size(G->g[v])) {
				u32 n = vector_at(G->g[v], j);
				if(G->color[n] == G->color[v]) {
					vector_destroy(stack);
					Greedy(G);
					return 1;
				}
				if(G->color[n] == ~0u) {
					G->color[n] = (G->color[v] + 1) % 2;
					vector_push_back(stack, n);
					G->x = 2;
				}
			}
		}
	}
	vector_destroy(stack);
	return 0;
}

#endif
