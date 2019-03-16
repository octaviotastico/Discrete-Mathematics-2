#ifndef COLOR_H
#define COLOR_H

#include "grafo.c"

u32 Greedy(Grafo G) {
	map m = map_create();
	u32 v, n, c;
	fore(i, 0, G->n) {
		v = vector_at(G->g[G->order[i]], 0);
		fore(j, 1, GradoDelVertice(G, v)) {
			n = vector_at(G->g[G->order[i]], j);
			map_add(m, ColorDelVertice(G, j), ColorDelVertice(G, j));
		}
		c = 0;
		while(map_find(m, c)) c++;
		G->color[v] = c;
		map_clear(m);
	}
}

int Bipartito(Grafo G) {
	u32 neighbour;
	u32 v; int visited[G->n], c = 0;
	memset(visited, 0, sizeof(visited));
	vector stack = vector_create();
	v = vector_at(G->g[G->order[0]], 0);
	vector_push_back(stack, v);
	G->color[v] = c; c++;
	while(!vector_empty(stack)) {
		v = vector_pop_back(stack);
		visited[v] = 1;
		fore(i, 0, GradoDelVertice(G, v)) {
			neighbour = NombreJotaesimoVecino(G, v, i);
			if(!visited[neighbour]) {
				vector_push_back(stack, neighbour);
				visited[neighbour] = 1;
				G->color[neighbour] = c;
			}
		}
		c = c == 1 ? 0 : 1;
	}
}

#endif
