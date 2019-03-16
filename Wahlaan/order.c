#include "grafo.c"

char OrdenNatural(Grafo G) {
    // We mapped the verteces to [0, ..., n - 1] in a way where if i < j then dict[i] < dict[j]
    // So an O(n) approch like this one could work

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
        vector_destroy(buckets[j]);
    }

    free(buckets);

    return 0;
}

char SwitchVertices(Grafo G, u32 i, u32 j) {
    if(i >= G->n || j >= G->n) return 1;
    G->order[i] ^= G->order[j];
    G->order[j] ^= G->order[i];
    G->order[i] ^= G->order[j];
    return 0;
}

char RMBCnormal(Grafo G) {
    // Invariant: There are x colors, from 0 to x - 1
    // So we can use bucket sort (with no internal ordering)

    // Create buckets
    vector* buckets = (vector*)malloc(G->x * sizeof(vector));
    if(!buckets) return 1;
    fore(i, 0, G->x) {
        buckets[i] = vector_create();
        if(!buckets[i]) {
            fore(j, 0, i) vector_destroy(buckets[i]);
            free(buckets);
            return 1;
        }
    }

    // Fill buckets
    fore(i, 0, G->n) {
        u32 c = ColorDelVertice(G, i);
        if(vector_push_back(buckets[c], G->order[i])) {
            fore(i, 0, G->x) vector_destroy(buckets[i]);
            free(buckets);
            return 1;
        }
    }

    // Fill order
    int i = 0;
    fore(j, 0, G->x) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
        vector_destroy(buckets[j]);
    }

    free(buckets);

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
    // We do a normal RMBC
    if(RMBCnormal(G)) return 1;

    // Now we can count for every color, how many of them there are
    u32* count = (u32*)malloc(G->x * sizeof(u32));
    if(!count) return 1;

    u32 maxcount = 0;

    fore(i, 0, G->n) {
        u32 c = ColorDelVertice(G, i);
        count[c]++;
        maxcount = (count[c] > maxcount) ? count[c] : maxcount;
    }

    // Now we create new buckets, using the count array to distribute

    // Create buckets
    vector* buckets = (vector*)malloc(maxcount * sizeof(vector));
    if(!buckets) return 1;
    fore(i, 0, maxcount) {
        buckets[i] = vector_create();
        if(!buckets[i]) {
            fore(j, 0, i) vector_destroy(buckets[i]);
            free(buckets);
            return 1;
        }
    }

    // Fill buckets
    fore(i, 0, G->n) {
        u32 c = ColorDelVertice(G, i);
        u32 cc = count[c];
        if(vector_push_back(buckets[cc - 1], G->order[i])) {
            fore(i, 0, maxcount) vector_destroy(buckets[i]);
            free(buckets);
            return 1;
        }
    }

    // Fill order
    int i = 0;
    fore(j, 0, maxcount) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
        vector_destroy(buckets[j]);
    }

    free(buckets);

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