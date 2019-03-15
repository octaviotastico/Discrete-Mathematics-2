#include "grafo.h"
#include "map.h"
#include "vector.h"

struct GrafoSt {
    u32 n, m, x;
    u32 *dict, *color, *order;
    vector* g;
};

char* get_line() {
    char* str = (char*)malloc(sizeof(char));
    if(!str) return str;
    size_t sz = 0, cap = 1;

    char ch;
    while(EOF != (ch = fgetc(stdin)) && ch != '\n') {
        str[sz++] = ch;
        if(sz == cap) {
            str = realloc(str, sizeof(char) * (cap *= 2));
            if(!str) return str;
        }
    }
    str[sz++] = '\0';

    return realloc(str, sizeof(char) * sz);
}



Grafo ConstruccionDelGrafo(void) {
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = G->m = G->x = 0;
    G->dict = G->color = G->order = NULL;
    G->g = NULL;

    char* line;

    // c *
    do {
        line = get_line();
    } while(line[0] == 'c');


    if(memcmp(line, "p edge", 6)) {
        free(G);
        return NULL;
    }

    // p edge n m
    int i = 7;
    while(line[i] != ' ') {
        G->n = (G->n * 10u) + line[i++] - '0';
    }
    i++;
    while(line[i] != '\0') {
        G->m = (G->m * 10u) + line[i++] - '0';
    }

    // e u v

    map m = map_create();
    G->g = (vector*)malloc(G->n * sizeof(vector));
    fore(i, 0, G->n) {
        G->g[i] = vector_create();
    }

    fore(i, 0, G->m) {
        line = get_line();
        if(line[0] != 'e') {
            map_destroy(m);
            fore(i, 0, G->n) {
                vector_destroy(G->g[i]);
            }
            free(G->g);
            free(G);
            return NULL;
        }
        int j = 2;
        u32 u = 0, v = 0;
        while(line[j] != ' ') {
            u = u * 10u + line[j++] - '0';
        }
        while(line[j] == ' ') j++;

        while(line[j] != '\0') {
            v = v * 10u + line[j++] - '0';
        }

        printf("%d %d\n", u, v);

        u32 real_u, real_v;
        u32* res;

        if((res = map_find(m, u)))
            real_u = *res;
        else 
            real_u = map_size(m), map_add(m, u, map_size(m));

        if((res = map_find(m, v)))
            real_v = *res;
        else 
            real_v = map_size(m), map_add(m, v, map_size(m));

        vector_push_back(G->g[real_u], real_v);
        vector_push_back(G->g[real_v], real_u);

        printf("%d %d %d %d\n", u, real_u, v, real_v);
    }
    return G;
}