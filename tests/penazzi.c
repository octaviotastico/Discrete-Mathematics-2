#include "checks.h"
#include "time.h"

void correrNatural(Grafo g) {
	doNatural(g);
	doGreedy(g);
	fprintf(stdout, "%u\n", NumeroDeColores(g));
}

void correrWelsh(Grafo g) {
	doWelsh(g);
	doGreedy(g);
	fprintf(stdout, "%u\n", NumeroDeColores(g));
}

void correrSwitch(Grafo g, int times) {
	srand(clock());
	u32 n = NumeroDeVertices(g);
	u32 x = NumeroDeColores(g);
	fore(i, 0, times) {
		int r1 = rand() % n;
		int r2 = rand() % n;
		SwitchVertices(g, r1, r2);
		doGreedy(g);
		x = min(x, NumeroDeColores(g));
	}
	fprintf(stdout, "%u\n", x);
}

void correrRMBC(Grafo g, int times) {
	srand(clock());
	u32 x = NumeroDeColores(g);
	fore(i, 0, times) {
		int r = rand() % 3;
		switch(r) {
			case 0:
				doRMBC(g);
				break;
			case 1:
				doRMBCr(g);
				break;
			case 2:
				doRMBCc(g);
				break;
		}
		doGreedy(g);
		x = min(x, NumeroDeColores(g));
	}
	fprintf(stdout, "%u\n", x);
}

int main() {

	Grafo g = ConstruccionDelGrafo();

	correrNatural(g);
	correrWelsh(g);
	correrSwitch(g, 100);
	correrRMBC(g, 1000);
	
	DestruccionDelGrafo(g);
	return 0;
}