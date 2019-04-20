#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {

	if(G->colored) return G->x;

	// Allocs the vectors
	u32* available = calloc(G->n, sizeof(u32));
	vector v = vector_create();

	if(!available || !v) return -1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	G->x = 0;

	fore(i, 0, G->n) {
		fore(j, 0, GradoDelVertice(G, i)) {
			u32 x = ColorJotaesimoVecino(G, i, j);
			if(x != ~0u && !available[x]) {
				available[x] = 1;
				if(vector_push_back(v, x) < 0) {
					free(available);
					return -1;
				}
			}
		}
		// Search the first avaible color
		u32 c = 0;
		while(available[c]) c++;
		// Assign color
		G->color[G->order[i]] = c;
		G->x = max(G->x, c + 1);
		while(!vector_empty(v)) available[vector_pop_back(v)] = 0;
	}
	free(available);
	vector_destroy(v);
	
	return G->x;
}

int Bipartito(Grafo G) {
	vector stack = vector_create();

	if(!stack) return -1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	G->x = 1;

	fore(i, 0, G-> n) if(G->color[i] == ~0u) {
		vector_push_back(stack, i);
		// Color first vertex
		G->color[i] = 0;
		while(!vector_empty(stack)) {
			u32 v = vector_pop_back(stack);
			// Add every neighbour of v
			fore(j, 0, vector_size(G->g[v])) {
				u32 n = vector_at(G->g[v], j);
				// If not possible
				if(G->color[n] == G->color[v]) {
					vector_destroy(stack);
					Greedy(G);
					return 0;
				}
				// If neighbour does not have color
				if(G->color[n] == ~0u) {
					G->color[n] = (G->color[v] + 1) % 2;
					vector_push_back(stack, n);
					G->x = 2;
				}
			}
		}
	}
	// Frees the resources
	vector_destroy(stack);
	return 1;
}

#endif
