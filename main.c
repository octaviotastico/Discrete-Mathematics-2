#include "Rii.h"

int main() {
	Grafo g = ConstruccionDelGrafo();

	OrdenWelshPowell(g);

	u32 n = NumeroDeVertices(g);

	fore(i, 0, n) {
		u32 w = GradoDelVertice(g, i);
		printf("%u ", w);
	} printf("\n");
	return 0;
}