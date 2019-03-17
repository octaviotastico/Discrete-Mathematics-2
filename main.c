#include "Rii.h"

int main() {
	Grafo g = ConstruccionDelGrafo();

	u32 n = NumeroDeVertices(g);


	RMBCnormal(g);
	fore(i, 0, n) {
		u32 c = ColorDelVertice(g, i);
		u32 n = NombreDelVertice(g, i);
		printf("%u:%u ", c, n);
	} printf("\n");

	RMBCrevierte(g);
	fore(i, 0, n) {
		u32 c = ColorDelVertice(g, i);
		u32 n = NombreDelVertice(g, i);
		printf("%u:%u ", c, n);
	} printf("\n");

	RMBCchicogrande(g);
	fore(i, 0, n) {
		u32 c = ColorDelVertice(g, i);
		u32 n = NombreDelVertice(g, i);
		printf("%u:%u ", c, n);
	} printf("\n");

	Greedy(g);

	Bipartito(g);

	DestruccionDelGrafo(g);
	
	return 0;
}