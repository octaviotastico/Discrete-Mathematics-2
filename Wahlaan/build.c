#include "grafo.c"

static char* get_line(char* line) {
    // Wipe previous line
    if(line) free(line);

    // Alloc space for line
    line = (char*)malloc(sizeof(char));
    if(!line) return line;

    size_t sz = 0, cap = 1;

    char c;
    while(EOF != (c = fgetc(stdin)) && c != '\n' && c != '\r') {
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

Grafo ConstruccionDelGrafo() {
    // Allocs the memory of the graph
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = G->m = G->x = 0;
    G->dict = G->color = G->order = NULL;
    G->g = NULL;

    char* line = NULL;

    // ----------------- READ COMMENTS ----------------- //
    do {
        line = get_line(line);
        if(!line) {
            DestruccionDelGrafo(G);
            printf("Fallo al leer\n");
            return NULL;
        }
    } while(line[0] == 'c');

    // ---------------- READ p edge n m ---------------- //

    // Compare the first part
    if(memcmp(line, "p edge ", 7)) {
        free_resources(G, line, NULL, NULL, NULL);
        printf("Error en primera linea sin comentario\n");
        return NULL;
    }

    // Start looking at pos 7
    u32 i = 7;

    // Read n
    while('0' <= line[i] && line[i] <= '9') {
        G->n = G->n * 10u + line[i++] - '0';
    }

    // Advance to m
    while('0' > line[i] || line[i] > '9') {
        if(line[i] == '\0') {
            free_resources(G, line, NULL, NULL, NULL);
            printf("Error en primera linea sin comentario\n");
        } else i++;
    }

    // Read m
    while('0' <= line[i] && line[i] <= '9') {
        G->m = G->m * 10u + line[i++] - '0';
    }

    // ---------------- ALLOC RESOURCES ---------------- //

    // Alloc map and adjacency list
    map m = map_create();
    G->g = (vector*)malloc(G->n * sizeof(vector));

    // Alloc the vectors for the adj. list
    fore(i, 0, G->n) {
        G->g[i] = vector_create();
        if(!G->g[i]) {
            free_resources(G, line, m, NULL, NULL);
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

    // If there was an error on any of the allocs, free the memory
    if(!m || !u || !v || !G->dict || !G->color || !G->order) {
        free_resources(G, line, m, u, v);
        printf("Fallo al reservar memoria\n");
        return NULL;
    }
    
    // ------------------ READ EDGES ------------------ //

    fore(i, 0, G->m) {
        line = get_line(line);
        if(!line) {
            free_resources(G, line, m, u, v);
            printf("Fallo al leer\n");
            return NULL;
        }

        // Compare the first part
        if(memcmp(line, "e ", 2)) {
            free_resources(G, line, m, u, v);
            printf("Error de lectura en lado %i\n", i + 1);
            return NULL;
        }

        // Start lookin at position 2
        u32 j = 2;

        // Read u
        while('0' <= line[j] && line[j] <= '9') {
            u[i] = u[i] * 10u + line[j++] - '0';
        }

        // Advance to v
        while('0' > line[j] || line[j] > '9') {
            if(line[j] == '\0') {
                free_resources(G, line, m, u, v);
                printf("Error de lectura en lado %i\n", i + 1);
            } else j++;
        }

        // Read v
        while('0' <= line[j] && line[j] <= '9') {
            v[i] = v[i] * 10u + line[j++] - '0';
        }

        // Add {u[i], 0} and {v[i], 0}
        if(map_add(m, u[i], 0) || map_add(m, v[i], 0)) {
            free_resources(G, line, m, u, v);
            printf("Fallo al agregar un nodo al mapa\n");
            return NULL;
        }
    }

    // Check G->n matches
    if(map_size(m) != G->n) {
        free_resources(G, line, m, u, v);
        printf("Cantidad de vértices leidos no es la declarada\n");
        return NULL;
    }

    // Default coloring: Ci = i
    G->x = G->n;
    fore(i, 0, G->n) G->color[i] = i;

    // Default order: Natural
    fore(i, 0, G->n) G->order[i] = i;

    // Map the smallest vertex to 0, the second smallest to 1, ..., the greatest to n - 1
    map_sort(m);

    // Construct adjacency list
    fore(i, 0, G->m) {
        // Find the mapping of u and v
        u32 real_u = *map_find(m, u[i]);
        u32 real_v = *map_find(m, v[i]);

        // Store them into the dictionary
        G->dict[real_u] = u[i];
        G->dict[real_v] = v[i];

        // Push the edges (real_u -> real_v and real_u <- real_v)
        if(vector_push_back(G->g[real_u], real_v) || vector_push_back(G->g[real_v], real_u)) {
            free_resources(G, line, m, u, v);
            printf("Fallo al crear una arista\n");
            return NULL;
        }
    }

    // Free resources
    free_resources(NULL, line, m, u, v);
    
    // Return graph
    return G;
}

Grafo CopiarGrafo(Grafo G) {
    // Creates the new graph
    Grafo copy = (Grafo)malloc(sizeof(struct GrafoSt));

    if(!copy) return NULL;

    // Copy number of vertex, edges, and number of colors
    copy->n = G->n;
    copy->m = G->m;
    copy->x = G->x;

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