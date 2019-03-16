#include "grafo.h"
#include "vector.h"
#include "map.h"

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

    // Read comments
    do {
        line = get_line();
        if(!line) {
            DestruccionDelGrafo(G);
            printf("Fallo al leer\n");
            return NULL;
        }
    } while(line[0] == 'c');

    // Check if this line is in the form 'p edge n m'
    if(memcmp(line, "p edge", 6)) {
        free(line);
        DestruccionDelGrafo(G);
        printf("error en primera linea sin comentario\n");
        return NULL;
    }

    // Get n and m
    int i = 7;
    while(line[i] != ' ') {
        G->n = (G->n * 10u) + line[i++] - '0';
    }
    i++;
    while(line[i] != '\0') {
        G->m = (G->m * 10u) + line[i++] - '0';
    }

    // ----------------- ALLOCS --------------------- //

    // Alloc map and adjacency list
    map m = map_create();
    G->g = (vector*)malloc(G->n * sizeof(vector));

    // Alloc the vectors for the adj. list
    fore(i, 0, G->n) {
        G->g[i] = vector_create();
        if(!G->g[i]) {
            DestruccionDelGrafo(G);
            printf("Fallo al reservar memoria para el vector %d", i);
            return NULL;
        }
    }

    // Alloc memory for edges
    u32* u = (u32*)malloc(G->m * sizeof(u32));
    u32* v = (u32*)malloc(G->m * sizeof(u32));

    G->dict = (u32*)malloc(G->n * sizeof(u32));
    G->color = (u32*)malloc(G->n * sizeof(u32));
    G->order = (u32*)malloc(G->n * sizeof(u32));

    if(!m || !u || !v || !G->g || !G->color || !G->color || !G->order) {
        if(m) free(m);
        if(u) free(u);
        if(v) free(v);
        DestruccionDelGrafo(G);
        printf("Fallo al reservar memoria\n");
        return NULL;
    }

    // ------------------------------------------------- //

    // Receive m edges
    fore(i, 0, G->m) {
        line = get_line();
        if(!line) {
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("error de lectura en lado L\n");
            return NULL;
        }
        // Check that the line is in the form 'e u v'
        if(line[0] != 'e') {
            free(line);
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("error de lectura en lado %i\n", i + 1);
            return NULL;
        }
        int j = 2;
        while(line[j] != ' ') {
            u[i] = u[i] * 10u + line[j++] - '0';
        }
        while(line[j] == ' ') j++;

        while(line[j] != '\0') {
            v[i] = v[i] * 10u + line[j++] - '0';
        }
        if(map_add(m, u[i], 0)) {
            free(line);
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("Fallo al agregar un nodo al mapa\n");
            return NULL;
        }
        if(map_add(m, v[i], 0)) {
            free(line);
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("Fallo al agregar un nodo al mapa\n");
            return NULL;
        }
    }

    // No more input
    free(line);

    if(map_size(m) != G->n) {
        free(m), free(u), free(v);
        DestruccionDelGrafo(G);
        printf("cantidad de vertices leidos no es la declarada\n");
        return NULL;
    }

    // No color
    fore(i, 0, G->n) G->color[i] = -1;
    // Natural order
    fore(i, 0, G->n) G->order[i] = i;

    // Map the smallest one with 0, the second smallest to 1, ..., the greatest to n - 1
    map_restructure(m);

    fore(i, 0, G->m) {
        u32 real_u = *map_find(m, u[i]);
        u32 real_v = *map_find(m, v[i]);
        G->dict[real_u] = u[i];
        G->dict[real_v] = v[i];
        if(vector_push_back(G->g[real_u], real_v)) {
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("Fallo al crear una arista\n");
            return NULL;
        }
        if(vector_push_back(G->g[real_v], real_u)) {
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("Fallo al crear una arista\n");
            return NULL;
        }
    }

    // u, v and m are not needed anymore memory
    free(u); free(v); map_destroy(m);

    // /* test
    
    fore(i, 0, G->n) {
        fore(j, 0, vector_size(G->g[i])) {
            printf("USUARIO: %d %d\n", G->dict[i], G->dict[vector_at(G->g[i], j)]);
            printf("SISTEMA: %d %d\n", i, vector_at(G->g[i], j));
        }
    }

    // */

    return G;
}

Grafo CopiarGrafo(Grafo G) {
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
    if(G->g){
        fore(i, 0, G->n)
            if(G->g[i])
                vector_destroy(G->g[i]);
        
        free(G->g);
        G->g = NULL;
    }
    if(G->dict) {
        free(G->dict);
        G->dict = NULL;
    }
    if(G->color) {
        free(G->color);
        G->color = NULL;
    }
    if(G->order) {
        free(G->order);
        G->order = NULL;
    }
    free(G);
    G = NULL;
}

u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

u32 NumeroDeLados(Grafo G) {
    return G->m;
}

u32 NumeroDeColores(Grafo G) {
    return G->x;
}
