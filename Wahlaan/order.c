#include "grafo.c"

static vector* create_buckets(size_t);

static void free_buckets(vector*, size_t);

char OrdenNatural(Grafo G) {
    // We mapped the verteces to [0, ..., n - 1] in a way where if i < j then dict[i] < dict[j]
    // So an O(n) approch like this one could work
    fore(i, 0, G->n) G->order[i] = i;
    return 0;
}

char OrdenWelshPowell(Grafo G) {
    // Invariant: Every node has at least n - 1 neighbours
    // So we can use bucket sort (with no internal ordering) to achieve O(n) sort
    vector* g = G->g;
    
    vector* buckets = create_buckets(G->n);

    if(!buckets) return 1;

    // Fill buckets
    u32 delta = 0;
    fore(i, 0, G->n) {
        u32 v = G->order[i];
        u32 w = vector_size(g[v]);
        if(vector_push_back(buckets[w], v) < 0) {
            free_buckets(buckets, G->n);
            return 1;
        }
        delta = max(w, delta);
    }

    // Fill order
    u32 i = 0;
    for(int j = delta; j >= 0; j--) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
    }

    free_buckets(buckets, G->n);

    return 0;
}

char SwitchVertices(Grafo G, u32 i, u32 j) {
    if(i >= G->n || j >= G->n) return 1;
    u32 aux = G->order[i];
    G->order[i] = G->order[j];
    G->order[j] = aux;

    return 0;
}

// bucket
char RMBCnormal(Grafo G) {
    // Invariant: There are x colors, from 0 to x - 1
    // So we can use bucket sort (with no internal ordering)    
    vector* buckets = create_buckets(G->n);

    if(!buckets) return 1;

    // Fill buckets
    fore(i, 0, G->n) {
        u32 v = G->order[i];
        u32 c = G->color[v];
        if(vector_push_back(buckets[c], v) < 0) {
            free_buckets(buckets, G->n);
            return 1;
        }
    }

    // Fill order
    int i = 0;
    fore(j, 0, G->n) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
    }

    free_buckets(buckets, G->n);

    return 0;
}

char RMBCrevierte(Grafo G) {
    // We do a normal RMBC
    if(RMBCnormal(G)) return 1;
    // We reverse the order in O(n)
    fore(i, 0, G->n / 2) {
        if(SwitchVertices(G, i, G->n - i - 1)) return 1;
    }

    return 0;
}

char RMBCchicogrande(Grafo G) {
    // If we do RMBC first, we will fill them in order of colors,
    // so we will take them by colors too, so its a valid RMBCc

    if(RMBCnormal(G)) return 1;
    
    // Now we can count for every color, how many of them there are    
    u32* count = (u32*)calloc(G->x, sizeof(u32));

    if(!count) return 1;

    u32 maxcount = 0;
    fore(i, 0, G->n) {
        u32 c = G->color[G->order[i]];
        count[c]++;
        maxcount = max(maxcount, count[c] + 1);
    }

    vector* buckets = create_buckets(maxcount);

    // Fill buckets
    fore(i, 0, G->n) {
        u32 v = G->order[i];
        u32 c = G->color[v];
        if(vector_push_back(buckets[count[c]], v) < 0) {
            free_buckets(buckets, G->n);
            return 1;
        }
    }

    // Fill order
    int i = 0;
    fore(j, 0, maxcount) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
    }

    free_buckets(buckets, maxcount);

    return 0;
}

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

static vector* create_buckets(size_t sz) {
    vector* buckets = (vector*)malloc(sz * sizeof(vector));
    if(!buckets) return NULL;

    fore(i, 0, sz) {
        buckets[i] = vector_create();
        if(!buckets[i]) {
            free_buckets(buckets, sz);
            return NULL;
        }
    }
    return buckets;
}

static void free_buckets(vector* buckets, size_t sz) {
    fore(i, 0, sz) if(buckets[i]) vector_destroy(buckets[i]);
    free(buckets);
}
