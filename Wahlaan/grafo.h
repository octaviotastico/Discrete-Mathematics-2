#ifndef GRAFO_H
#define GRAFO_H

#include "Rii.h"

typedef struct GrafoSt* Grafo;

// grafo.c

Grafo ConstruccionDelGrafo(void);

Grafo CopiarGrafo(Grafo);

void DestruccionDelGrafo(Grafo);

// queries.c

u32 NumeroDeVertices(Grafo);

u32 NumeroDeLados(Grafo);

u32 NumeroDeColores(Grafo);

u32 NombreDelVertice(Grafo, u32);

u32 GradoDelVertice(Grafo, u32);

u32 ColorDelVertice(Grafo, u32);

u32 ColorJotaesimoVecino(Grafo, u32, u32);

u32 NombreJotaesimoVecino(Grafo, u32, u32);


// order.c

char OrdenNatural(Grafo);

char OrdenWelshPowell(Grafo);

char SwitchVertices(Grafo, u32, u32);

char RMBCnormal(Grafo);

char RMBCrevierte(Grafo);

char RMBCchicogrande(Grafo);

char SwitchColores(Grafo, u32, u32);

#endif