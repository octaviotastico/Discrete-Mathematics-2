#ifndef GRAFO_C
#define GRAFO_C

#include "grafo.h"

struct GrafoSt {
    u32 n;           // Number of verteces
    u32 m;           // Number of edges
    u32 x;           // Number of colors
    u32 d;           // Max number of neighbors of a vertex
    u32* dict;       // Map to nodes
    u32* color;      // Array with colors
    u32* order;      // Order of vertex
    vector* g;       // Adjacency list
};

#endif
