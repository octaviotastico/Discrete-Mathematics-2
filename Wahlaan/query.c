#include "grafo.c"

// Returns the number of vertex in G.
u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

// Returns the number of edges in G.
u32 NumeroDeLados(Grafo G) {
    return G->m;
}

// Returns the number of different colors in G.
u32 NumeroDeColores(Grafo G) {
    return G->x;
}

// Returns the number of the vertex in the given position.
u32 NombreDelVertice(Grafo G, u32 i) {
    return G->dict[G->order[i]];
}

// Returns the color of the given vertex. Otherwise 2^32-1.
u32 ColorDelVertice(Grafo G, u32 i) {
    return G->color[G->order[i]];
}

// Returns the vertex adjacency in the given position.
u32 GradoDelVertice(Grafo G, u32 i) {
    return vector_size(G->g[G->order[i]]);
}

// Returns the color of the given neighbour of the given vertex.
u32 ColorJotaesimoVecino(Grafo G, u32 i, u32 j) {
    return G->color[vector_at(G->g[G->order[i]], j)];
}

// Returns the number of the given neighbour of the given vertex.
u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j) {
    return G->dict[vector_at(G->g[G->order[i]], j)];
}