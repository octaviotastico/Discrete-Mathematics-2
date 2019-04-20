#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {

	// Allocs the vectors
	u32* available = calloc(G->n, sizeof(u32));
	vector used = vector_create();

	if(!available || !used) return -1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	G->x = 0;

	vector* g = G->g;

	fore(i, 0, G->n) {
		int v = G->order[i];
		fore(j, 0, vector_size(g[v])) {
			u32 x = G->color[vector_at(g[v], j)];
			if(x != ~0u && !available[x]) {
				available[x] = 1;
				if(vector_push_back(used, x) < 0) {
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
		// Update number of colors
		G->x = max(G->x, c + 1);
		// Set used positions to zero
		while(!vector_empty(used)) available[vector_pop_back(used)] = 0;
	}

	free(available);
	vector_destroy(used);
	
	return G->x;
}

int Bipartito(Grafo G) {
	vector stack = vector_create();

	if(!stack) return -1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	G->x = 1;

	vector* g = G->g;

	fore(i, 0, G-> n) if(G->color[i] == ~0u) {
		vector_push_back(stack, i);
		G->color[i] = 0;
		while(!vector_empty(stack)) {
			u32 v = vector_pop_back(stack);
			// Add every neighbour of v
			fore(j, 0, vector_size(g[v])) {
				u32 n = vector_at(g[v], j);
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
	vector_destroy(stack);
	return 1;
}

#endif
