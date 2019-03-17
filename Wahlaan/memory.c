#include "grafo.c"

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

    char* line = NULL;

    // Read comments
    do {
        if(line) free(line);
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
        printf("Error en primera linea sin comentario\n");
        return NULL;
    }

    // Get n and m (n starts at position 7)
    int i = 7;
    while(line[i] != ' ') {
        G->n = G->n * 10u + line[i++] - '0';
    }
    i++;
    while(line[i] != '\0') {
        G->m = G->m * 10u + line[i++] - '0';
    }

    free(line);

    // ------------------- ALLOCS ------------------- //

    // Alloc map and adjacency list
    map m = map_create();
    G->g = (vector*)malloc(G->n * sizeof(vector));

    // Alloc the vectors for the adj. list
    fore(i, 0, G->n) {
        G->g[i] = vector_create();
        if(!G->g[i]) {
            free(line);
            if(m) free(m);
            DestruccionDelGrafo(G);
            printf("Fallo al reservar memoria para el vector %d", i);
            return NULL;
        }
    }

    // Alloc memory for edges
    u32* u = (u32*)calloc(G->m, sizeof(u32));
    u32* v = (u32*)calloc(G->m, sizeof(u32));

    // Alloc memory por dictionary, array of colors and order

    G->dict  = (u32*)malloc(G->n * sizeof(u32));
    G->color = (u32*)malloc(G->n * sizeof(u32));
    G->order = (u32*)malloc(G->n * sizeof(u32));

    if(!m || !u || !v || !G->dict || !G->color || !G->order) {
        free(line);
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
            printf("Fallo al leer\n");
            return NULL;
        }
        // Check that the line is in the form 'e u v'
        if(line[0] != 'e') {
            free(line);
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("Error de lectura en lado %i\n", i + 1);
            return NULL;
        }

        // Read u and v
        int j = 2;
        while(line[j] != ' ') {
            u[i] = u[i] * 10u + line[j++] - '0';
        }
        while(line[++j] == ' ');

        while(line[j] != '\0') {
            v[i] = v[i] * 10u + line[j++] - '0';
        }

        // Add them to map

        if(map_add(m, u[i], 0) || map_add(m, v[i], 0)) {
            free(line);
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("Fallo al agregar un nodo al mapa\n");
            return NULL;
        }
        free(line);
    }

    if(map_size(m) != G->n) {
        free(m), free(u), free(v);
        DestruccionDelGrafo(G);
        printf("Cantidad de vertices leidos no es la declarada\n");
        return NULL;
    }

    // Default coloring: Ci = i
    G->x = G->n;
    fore(i, 0, G->n) G->color[i] = i;

    // Default order: Natural
    fore(i, 0, G->n) G->order[i] = i;

    // Map the smallest vertex to 0, the second smallest to 1, ..., the greatest to n - 1
    map_sort(m);

    // Construct the adjacency list
    fore(i, 0, G->m) {
        // Find the mapping of u and v
        u32 real_u = *map_find(m, u[i]);
        u32 real_v = *map_find(m, v[i]);

        // Store them into the dictionary
        G->dict[real_u] = u[i];
        G->dict[real_v] = v[i];

        // Push the edges (u -> v and u <- v)
        if(vector_push_back(G->g[real_u], real_v) || vector_push_back(G->g[real_v], real_u)) {
            free(m), free(u), free(v);
            DestruccionDelGrafo(G);
            printf("Fallo al crear una arista\n");
            return NULL;
        }
    }

    free(u); free(v);

    map_destroy(m);
    
    return G;
}

Grafo CopiarGrafo(Grafo G) {
    Grafo copy = (Grafo)malloc(sizeof(struct GrafoSt));

    if(!copy) return NULL;

    copy->n = G->n;
    copy->m = G->m;
    copy->x = G->x;

    copy->g = (vector*)malloc(copy->n * sizeof(vector));
    copy->dict = (u32*)malloc(copy->n * sizeof(u32));
    copy->color = (u32*)malloc(copy->n * sizeof(u32));
    copy->order = (u32*)malloc(copy->n * sizeof(u32));

    if(!copy->g || !copy->dict || !copy->color || !copy->order) {
        DestruccionDelGrafo(copy);
        return NULL;
    }

    fore(i, 0, copy->n) {
        copy->color[i] = G->color[i];
        copy->order[i] = G->order[i];
        copy->dict[i] = G->dict[i];

        copy->g[i] = vector_create();
        if(!copy->g[i]) {
            DestruccionDelGrafo(G);
            return NULL;
        }

        fore(j, 0, vector_size(G->g[i])) {
            u32 v = vector_at(G->g[i], j);
            if(vector_push_back(copy->g[i], v)) {
                DestruccionDelGrafo(copy);
                return NULL;
            }
        }
    }

    return copy;
}

// Frees all the memory used by the graph.
void DestruccionDelGrafo(Grafo G) {
    if(G->g){
        fore(i, 0, G->n)
            if(G->g[i])
                vector_destroy(G->g[i]);
        
        free(G->g);
    }
    if(G->dict)  free(G->dict);
    if(G->color) free(G->color);
    if(G->order) free(G->order);
    free(G);
}