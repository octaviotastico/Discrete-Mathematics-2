#include "grafo.c"

static char* get_line(char*);

static int read_numbers(char*, u32, u32*, u32*);

static void free_resources(Grafo, char*, map, u32*, u32*);

Grafo ConstruccionDelGrafo() {
    // Allocs the memory of the graph
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = G->m = G->x = 0;
    G->dict = G->color = G->order = NULL;
    G->g = NULL;

    if(!G) {
        printf("fallo al reservar memoria para la estructura GrafoSt\n");
        return NULL;
    }

    char* line = NULL;

    // ----------------- READ COMMENTS ----------------- //
    do {
        line = get_line(line);
        if(!line) {
            free_resources(G, line, NULL, NULL, NULL);
            printf("fallo al leer\n");
            return NULL;
        }
    } while(line[0] == 'c');

    // ---------------- READ p edge n m ---------------- //

    // Compare the first part
    if(memcmp(line, "p edge ", 7)) {
        free_resources(G, line, NULL, NULL, NULL);
        printf("error en primera linea sin comentario\n");
        return NULL;
    }

    // Read n, m
    if(read_numbers(line, 7, &G->n, &G->m) < 0) {
        free_resources(G, line, NULL, NULL, NULL);
        printf("error en primera linea sin comentario\n");
        return NULL;
    }

    // ---------------- ALLOC RESOURCES ---------------- //

    // Alloc map and adjacency list
    map m = map_create();
    G->g = (vector*)malloc(G->n * sizeof(vector));

    /*
    No se controla que G->g se haya podido allocar
    Crear una funcion que devuelva un vector*,
    allocando todo lo de adentro, que devuelva -1 en caso de error
    */

    // Alloc the vectors for the adj. list
    fore(i, 0, G->n) {
        G->g[i] = vector_create();
        if(!G->g[i]) {
            free_resources(G, line, m, NULL, NULL);
            printf("fallo al reservar memoria para el vector %u\n", i);
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

    // If there was an error on any of the allocs, free the memory
    if(!m || !u || !v || !G->dict || !G->color || !G->order) {
        free_resources(G, line, m, u, v);
        printf("fallo al reservar memoria\n");
        return NULL;
    }
    
    // ------------------ READ EDGES ------------------ //
    
    fore(i, 0, G->m) {
        line = get_line(line);
        if(!line) {
            free_resources(G, line, m, u, v);
            printf("fallo al leer\n");
            return NULL;
        }

        // Compare the first part
        if(memcmp(line, "e ", 2)) {
            free_resources(G, line, m, u, v);
            printf("error de lectura en lado %u\n", i + 1);
            return NULL;
        }

        // Read u and v
        read_numbers(line, 2, &u[i], &v[i]);

        // Add {u[i], 0} and {v[i], 0} to tree
        if(map_add(m, u[i], 0) < 0 || map_add(m, v[i], 0) < 0) {
            free_resources(G, line, m, u, v);
            printf("fallo al agregar un nodo al mapa\n");
            return NULL;
        }
    }

    // Check G->n matches
    if(map_size(m) != G->n) {
        free_resources(G, line, m, u, v);
        printf("cantidad de vértices leidos no es la declarada\n");
        return NULL;
    }

    // Default order: Natural
    OrdenNatural(G);

    // Map the smallest vertex to 0, the second smallest to 1, ..., the greatest to n - 1
    map_sort(m);

    // Construct adjacency list
    fore(i, 0, G->m) {
        // Find the mapping of u and v
        u32 real_u = *map_find(m, u[i]);
        u32 real_v = *map_find(m, v[i]);

        // Store their names into the dictionary
        G->dict[real_u] = u[i];
        G->dict[real_v] = v[i];

        // Push edges real_u -> real_v and real_u <- real_v
        if(vector_push_back(G->g[real_u], real_v) < 0 || vector_push_back(G->g[real_v], real_u) < 0) {
            free_resources(G, line, m, u, v);
            printf("Fallo al crear una arista\n");
            return NULL;
        }
    }

    // Free resources
    free_resources(NULL, line, m, u, v);

    // Run Greedy
    Greedy(G);
    
    // Return graph
    return G;
}

Grafo CopiarGrafo(Grafo G) {
    // Creates the new graph
    Grafo copy = (Grafo)malloc(sizeof(struct GrafoSt));

    /* Modificar aca tambien, como arriba */

    if(!copy) return NULL;

    // Copy number of vertex, edges, and number of colors
    copy->n = G->n;
    copy->m = G->m;
    copy->x = G->x;
    
    // Copy current state
    strcpy(copy->current, G->current);
    copy->colored = G->colored;

    // Allocs the vectors and arrays for verteces and colors
    copy->g = (vector*)malloc(copy->n * sizeof(vector));
    copy->dict = (u32*)malloc(copy->n * sizeof(u32));
    copy->color = (u32*)malloc(copy->n * sizeof(u32));
    copy->order = (u32*)malloc(copy->n * sizeof(u32));

    // If any of the previous allocs failed, destroy resources
    if(!copy->g || !copy->dict || !copy->color || !copy->order) {
        DestruccionDelGrafo(copy);
        return NULL;
    }

    fore(i, 0, copy->n) {
        // Copy coloring and order
        copy->color[i] = G->color[i];
        copy->order[i] = G->order[i];
        copy->dict[i] = G->dict[i];

        // Allocs the neighbours for every vertex
        copy->g[i] = vector_create();
        if(!copy->g[i]) {
            DestruccionDelGrafo(copy);
            return NULL;
        }

        // Copy the adjacency of every vertex
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

void DestruccionDelGrafo(Grafo G) {
    if(G->g){
        fore(i, 0, G->n) if(G->g[i]) vector_destroy(G->g[i]);
        free(G->g);
    }
    if(G->dict)  free(G->dict);
    if(G->color) free(G->color);
    if(G->order) free(G->order);
    free(G);
}

static char* get_line(char* line) {
    // Wipe previous line
    if(line) free(line);

    // Alloc space for line
    line = (char*)malloc(sizeof(char));
    if(!line) return line;

    size_t sz = 0, cap = 1;

    char c;
    while(EOF != (c = fgetc(stdin)) && c != '\n' && c != '\r' && c != '\0') {
        line[sz++] = c;
        if(sz == cap) {
            line = realloc(line, sizeof(char) * (cap *= 2));
            if(!line) return line;
        }
    }

    // Add null character to line
    line[sz++] = '\0';

    // Give the line its real size
    return realloc(line, sizeof(char) * sz);
}

static int read_numbers(char* line, u32 i, u32* u, u32* v) {
    // Check the first number starts at i
    if('0' > line[i] && line[i] > '9') return -1;
    // Init both numbers
    *u = *v = 0;
    // Read first number
    while('0' <= line[i] && line[i] <= '9') {
        *u = *u * 10 + line[i++] - '0';
    }
    // Advance to second number
    while('0' > line[i] || line[i] > '9') if(line[i++] != ' ') return -1;

    // Read second number
    while('0' <= line[i] && line[i] <= '9') {
        *v = *v * 10 + line[i++] - '0';
    }
    // Check that the trailing part are space characters
    while(('0' > line[i] || line[i] > '9') && line[i] != '\0') if(line[i++] != ' ') return -1;
    return 0;
}

static void free_resources(Grafo g, char* line, map m, u32* u, u32* v) {
    // Destroy graph
    if(g) DestruccionDelGrafo(g);
    // Destroy buffer-input
    if(line) free(line);
    // Destroy map
    if(m) map_destroy(m);
    // Destroy edges
    if(u) free(u);
    if(v) free(v);
}