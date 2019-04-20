#include "grafo.c"

char OrdenNatural(Grafo G) {
    // If it's already sorted this way
    if(strncmp(G->current, "Nat", 3) == 0) return 0;

    // We mapped the verteces to [0, ..., n - 1] in a way where if i < j then dict[i] < dict[j]
    // So an O(n) approch like this one could work
    fore(i, 0, G->n) {
        G->order[i] = i;
    }
    strcpy(G->current, "Nat");
    
    G->colored = false;

    return 0;
}

char OrdenWelshPowell(Grafo G) {
    // If it's already sorted this way
    if(strncmp(G->current, "Welsh", 5) == 0) return 0;

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

    u32 delta = 0;

    // Fill buckets
    fore(i, 0, G->n) {
        u32 w = GradoDelVertice(G, i);
        if(vector_push_back(buckets[w], G->order[i])) {
            fore(j, 0, G->n) if(j != i) vector_destroy(buckets[j]);
            free(buckets);
            return 1;
        }
        delta = max(w, delta);
    }

    // Fill order
    int i = 0;
    for(int j = delta; j >= 0; j--) {
        fore(k, 0, vector_size(buckets[j])) {
            G->order[i++] = vector_at(buckets[j], k);
        }
        vector_destroy(buckets[j]);
    }

    fore(i, delta + 1, G->n) vector_destroy(buckets[i]);

    free(buckets);

    strcpy(G->current, "Welsh");

    G->colored = false;

    return 0;
}

char SwitchVertices(Grafo G, u32 i, u32 j) {
    if(i >= G->n || j >= G->n) return 1;
    u32 aux = G->order[i];
    G->order[i] = G->order[j];
    G->order[j] = aux;
    strcpy(G->current, "SWv");
    
    G->colored = false;

    return 0;
}

char RMBCnormal(Grafo G) {
    // If it's already sorted this way
    if(strncmp(G->current, "RMBCn", 5) == 0) return 0;

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
            fore(j, 0, G->x) if(j != i) vector_destroy(buckets[j]);
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

    strcpy(G->current, "RMBCn");

    G->colored = false;

    return 0;
}

char RMBCrevierte(Grafo G) {
    // If it's already sorted this way
    if(strncmp(G->current, "RMBCr", 5) == 0) return 0;
    
    // We do a normal RMBC
    if(RMBCnormal(G)) return 1;

    // We reverse the order in O(n)
    fore(i, 0, G->n / 2) {
        if(SwitchVertices(G, i, G->n - i - 1)) return 1;
    }

    strcpy(G->current, "RMBCr");

    G->colored = false;

    return 0;
}

char RMBCchicogrande(Grafo G) {
    // If it's already sorted this way
    if(strncmp(G->current, "RMBCc", 5) == 0) return 0;
    
    // We do a normal RMBC
    if(RMBCnormal(G)) return 1;

    // Now we can count for every color, how many of them there are
    u32* count = (u32*)calloc(G->x, sizeof(u32));
    if(!count) return 1;

    u32 maxcount = 0;

    fore(i, 0, G->n) {
        u32 c = ColorDelVertice(G, i);
        count[c]++;
        maxcount = max(maxcount, count[c]);
    }

    // Now we create new buckets, using the count array to distribute

    // Create buckets
    vector* buckets = (vector*)malloc(maxcount * sizeof(vector));
    if(!buckets) return 1;

    fore(i, 0, maxcount) {
        buckets[i] = vector_create();
        if(!buckets[i]) {
            fore(j, 0, i) vector_destroy(buckets[i]);
            free(count);
            free(buckets);
            return 1;
        }
    }

    // Fill buckets
    fore(i, 0, G->n) {
        u32 c = ColorDelVertice(G, i);
        u32 cc = count[c];
        if(vector_push_back(buckets[cc - 1], G->order[i])) {
            fore(j, 0, maxcount) if(j != i) vector_destroy(buckets[j]);
            free(count);
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

    free(count);
    free(buckets);

    strcpy(G->current, "RMBCc");

    G->colored = false;

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

    strcpy(G->current, "SWc");

    G->colored = false;

    return 0;
}