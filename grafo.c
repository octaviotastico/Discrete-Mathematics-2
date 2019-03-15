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