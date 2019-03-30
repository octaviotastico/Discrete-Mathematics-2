#include "checks.h"

int main() {

	Grafo g = ConstruccionDelGrafo();

	fore(i, 0, 30) {
		int r = rand() % 5;
		switch(r) {
			case 0:
				doNatural(g);
				printf("Natural order: ");
				break;
			case 1:
				doWelsh(g);
				printf("Welsh order: ");
				break;
			case 2:
				doRMBC(g);
				printf("RMBC order: ");
				break;
			case 3:
				doRMBCr(g);
				printf("RMBCr order: ");
				break;
			case 4:
				doRMBCr(g);
				printf("RMBCr order: ");
				break;
		}
		doGreedy(g);
		printf("%u\n", NumeroDeColores(g));
	}
	return 0;
}