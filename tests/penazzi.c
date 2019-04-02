#include "checks.h"

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

void correrSwitch(Grafo g, u32 times) {
	srand(rand());
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

void correrRMBC(Grafo g, u32 times) {
	srand(rand());
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

int main(int argc, char *argv[]) {
	
	if(argc < 3) return -1;

	u32 sw = atoi(argv[1]);
	u32 rm = atoi(argv[2]);

	Grafo g = ConstruccionDelGrafo();
	
	correrNatural(g);
	correrWelsh(g);
	correrSwitch(g, sw);
	correrRMBC(g, rm);

	DestruccionDelGrafo(g);
	return 0;
}