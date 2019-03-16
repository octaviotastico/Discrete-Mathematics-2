#include "Rii.h"

int main() {
	Grafo g = ConstruccionDelGrafo();

	OrdenWelshPowell(g);

	u32 n = NumeroDeVertices(g);

	fore(i, 0, n) {
		u32 w = GradoDelVertice(g, i);
		printf("%u ", w);
	} printf("\n");

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
	
	return 0;
}