#include "grafo.c"

static inline vector* create_buckets(size_t);

static inline void fill_order(Grafo, vector*, size_t);

static inline void free_buckets(vector*, size_t);

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
    
    vector* buckets = create_buckets(G->d + 1);

    if(!buckets) return 1;

    // Fill buckets
    fore(i, 0, G->n) {
        u32 v = G->order[i];
        u32 w = vector_size(g[v]);
        if(vector_push_back(buckets[G->d - w], v) < 0) {
            free_buckets(buckets, G->n);
            return 1;
        }
    }

    // Fill order
    fill_order(G, buckets, G->d + 1);

    free_buckets(buckets, G->d + 1);

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
    vector* buckets = create_buckets(G->x);

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
    fill_order(G, buckets, G->x);

    free_buckets(buckets, G->x);

    return 0;
}

char RMBCrevierte(Grafo G) {
    // Invariant: There are x colors, from 0 to x - 1
    // So we can use bucket sort (with no internal ordering)    
    vector* buckets = create_buckets(G->x);

    if(!buckets) return 1;

    // Fill buckets
    fore(i, 0, G->n) {
        u32 v = G->order[i];
        u32 c = G->color[v];
        // Reverse order
        if(vector_push_back(buckets[G->x - 1 - c], v) < 0) {
            free_buckets(buckets, G->n);
            return 1;
        }
    }

    // Fill order
    fill_order(G, buckets, G->x);

    free_buckets(buckets, G->x);

    return 0;
}

char RMBCchicogrande(Grafo G) {
    // If we do RMBC first, we will fill them in order of colors,
    // so we will take them by color blocks too, so its a valid RMBCc

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
    fill_order(G, buckets, maxcount);

    free_buckets(buckets, maxcount);
    free(count);
    
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

static inline vector* create_buckets(size_t sz) {
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

static inline void fill_order(Grafo G, vector* buckets, size_t sz) {
    int i = 0;
    fore(j, 0, sz) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
    }
}

static inline void free_buckets(vector* buckets, size_t sz) {
    fore(i, 0, sz) if(buckets[i]) vector_destroy(buckets[i]);
    free(buckets);
}
