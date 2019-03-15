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
    G->dict = G->color = G->order = NULL;
    G->n = G->m = G->x = 0;
    G->g = NULL;

    char* line;

    do {
        line = get_line();
    } while(line[0] == 'c');

    int i = 7;
    while(line[i] != ' ') {
        G->n = (G->n * 10) + line[i++] - '0';
    }
    i++;
    while(line[i] != '\0') {
        G->m = (G->m * 10) + line[i++] - '0';
    }
    
    fore(i, 0, G->m) {
        line = get_line();
        int j = 3;
        int u = 0, v = 0;
        while(line[j] != ' ') {
            u = u * 10 + line[j++] - '0';
        }
        while(line[j] == ' ') j++;
        while(line[j] != '\0') {
            v = v * 10 + line[j++] - '0';
        }
    }
}

Grafo CopiarGrafo(Grafo G) {
    // ENOMEM = 12, i.e out of memory.
    Grafo copy = (Grafo)malloc(sizeof(struct GrafoSt));
    if(copy){
        memcpy(&G, &copy, sizeof G);
        //copy->dict = G->dict;
        //copy->color = G->color;
        //copy->order = G->order;
        //copy->n = G->n;
        //copy->m = G->m;
        //copy->x = G->x;
        //copy->g = G->g;
    }

    return copy;
}

void DestruccionDelGrafo(Grafo G) {
    vector_destroy(G->g);
    free(G); G = NULL;
}

u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

u32 NumeroDeLados(Grafo G) {
    return G->m;
}

u32 NumeroDeColores(Grafo G) {
    return (*G->color);
}
