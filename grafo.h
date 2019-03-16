#ifndef GRAFO
#define GRAFO

#include "defs.h"

typedef struct GrafoSt* Grafo;

Grafo ConstruccionDelGrafo(void);

void DestruccionDelGrafo(Grafo G);

#endif