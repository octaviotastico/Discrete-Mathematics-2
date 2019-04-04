#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {
	// Allocs the vectors
	u32* available = calloc(G->n, sizeof(u32));
	vector v = vector_create();

	// If any of the allocs failed, return an error
	if(!available || !v) return 1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	// Set total colors to 0
	G->x = 0;

	// For every vertex in G...
	fore(i, 0, G->n) {
		// For every neighbour of vertex i...
		fore(j, 0, GradoDelVertice(G, i)) {
			// Get it's color, and check if it's avaible or not
			u32 x = ColorJotaesimoVecino(G, i, j);
			// If it's a colored vertex, set it as not avaible
			if(x != ~0u && !available[x]) {
				available[x] = 1;
				if(vector_push_back(v, x)) {
					free(available);
					return 1;
				}
			}
		}
		u32 c = 0;
		// Search the first avaible color
		while(available[c]) c++;
		G->color[G->order[i]] = c;
		G->x = max(G->x, c + 1);
		while(!vector_empty(v)) available[vector_pop_back(v)] = 0;
	}
	// Frees the resources
	free(available);
	vector_destroy(v);
	return 0;
}

int Bipartito(Grafo G) {
	// Allocs the vectors
	vector stack = vector_create();

	// If any of the allocs failed, return an error
	if(!stack) return 1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	// Set total colors to 1
	G->x = 1;

	// For each connected component in G...
	fore(i, 0, G-> n) if(G->color[i] == ~0u) {
		// If we haven't looked for it before, push it to stack
		vector_push_back(stack, i);
		G->color[i] = 0; // Color to 0 (we haven't been there so there's no problem)
		while(!vector_empty(stack)) {
			u32 v = vector_pop_back(stack);
			// For every the neighbours of that vertex...
			fore(j, 0, vector_size(G->g[v])) {
				u32 n = vector_at(G->g[v], j); // Look at it's color
				// If it's not bipartito, run Greedy
				if(G->color[n] == G->color[v]) {
					vector_destroy(stack);
					Greedy(G);
					return 1;
				}
				// Else, color it
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
	return 0;
}

#endif
