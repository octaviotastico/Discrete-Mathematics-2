#include "grafo.c"

char OrdenNatural(Grafo G) {
    fore(i, 0, G->n) {
        G->order[i] = i;
    }
    return 0;
}

char OrdenWelshPowell(Grafo G) {
    // Invariant: Every node has at least n - 1 neighbours
    // So we can use bucket sort (with no internal ordering) to achieve O(n) sort

    // Create buckets

    vector* buckets = (vector*)malloc(G->n * sizeof(vector));
    if(!buckets) return 1;
    fore(i, 0, G->n) {
        buckets[i] = vector_create();
        if(!buckets[i]) {
            fore(j, 0, i) vector_destroy(buckets[i]);
            free(buckets);
            return 1;
        }
    }

    // Fill buckets

    fore(i, 0, G->n) {
        u32 w = GradoDelVertice(G, i);
        if(vector_push_back(buckets[w], G->order[i])) {
            fore(i, 0, G->n) vector_destroy(buckets[i]);
            free(buckets);
            return 1;
        }
    }

    // Fill order
    int i = 0;
    for(u32 j = G->n - 1u; j < G->n; j--) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
    }

    return 0;
}

char SwitchVertices(Grafo G, u32 i, u32 j) {
    if(i >= G->n || j >= G->n) return 1;
    G->order[i] ^= G->order[j];
    G->order[j] ^= G->order[i];
    G->order[i] ^= G->order[j];
    return 0;
}

char RMBCnormal(Grafo G);

char RMBCrevierte(Grafo G);

char RMBCchicogrande(Grafo G);

char SwitchColores(Grafo G, u32 i, u32 j) {
    if(i >= G->x || j >= G->x) return 1;
    fore(k, 0, G->n) {
        if(G->color[k] == i)
            G->color[k] = j;
        else if(G->color[k] == j)
            G->color[k] = i;
    }
    return 0;
}