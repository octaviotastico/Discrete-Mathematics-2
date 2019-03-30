#include "checks.h"

static void properColoring(Grafo g, u32 x) {
    u32 n = NumeroDeVertices(g);
    u32 y = 0;
    fore(i, 0, n) {
        u32 d = GradoDelVertice(g, i);
        u32 c = ColorDelVertice(g, i);
        y = max(y, c);
        fore(j, 0, d) {
            assert(ColorJotaesimoVecino(g, i, j) != c);
        }
    }
    assert(y + 1 == x);
}

void doGreedy(Grafo g) {
    // Greedy
    Greedy(g);
    // Check correct coloring
    properColoring(g, NumeroDeColores(g));
}

void doBipartito(Grafo g) {
    // Bipartito
    Bipartito(g);
    // Check correct coloring
    properColoring(g, NumeroDeColores(g));
}