#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {

	// Allocs the vectors
	u32* available = (u32*)calloc(G->n, sizeof(u32));
	u32* used = (u32*)calloc(G->n, sizeof(u32));

	if(!available || !used) return -1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	G->x = 0;

	vector* g = G->g;
	u32 index = 0;

	fore(i, 0, G->n) {
		int v = G->order[i];
		// Check every of it's neighbours
		fore(j, 0, vector_size(g[v])) {
			u32 x = G->color[vector_at(g[v], j)];
			// If vertex has color and was not marked as unavailable
			if(x != ~0u && !available[x]) {
				available[x] = 1;
				used[index++] = x;
			}
		}
		// Search the first available color
		u32 c = 0;
		while(available[c]) c++;
		// Assign color
		G->color[G->order[i]] = c;
		// Update number of colors
		G->x = max(G->x, c + 1);
		// Set used positions to zero
		while(index) available[used[--index]] = 0;
	}

	free(available);
	free(used);
	
	return G->x;
}

int Bipartito(Grafo G) {
	u32* stack = (u32*)calloc(G->n, sizeof(u32));

	if(!stack) return -1;

	// Set the coloring to -1 (2^32 - 1 in unsigned int)
	memset(G->color, ~0u, G->n * sizeof(u32));

	G->x = 1;

	vector* g = G->g;
	u32 index = 0;

	fore(i, 0, G->n) if(G->color[i] == ~0u) {
		// First vertex of the component
		stack[index++] = i;
		// Color it
		G->color[i] = 0;
		// While vertices on component
		while(index) {
			// Grab first element
			u32 v = stack[--index];
			// Check every neighbour
			fore(j, 0, vector_size(g[v])) {
				u32 n = vector_at(g[v], j);
				// If not possible, run greedy and return
				if(G->color[n] == G->color[v]) {
					free(stack);
					Greedy(G);
					return 0;
				}
				// If neighbour does not have color, color and push it
				if(G->color[n] == ~0u) {
					G->color[n] = (G->color[v] + 1) % 2;
					stack[index++] = n;
					G->x = 2;
				}
			}
		}
	}
	free(stack);
	return 1;
}

#endif
