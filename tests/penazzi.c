#include "checks.h"

int main(int argc, char *argv[]) {
	
	if(argc < 3) return -1;

	u32 sw = atoi(argv[1]);
	u32 rm = atoi(argv[2]);

	Grafo g = ConstruccionDelGrafo();
	
	correrNatural(&g, 1);
	correrWelsh(&g, 1);
	correrSwitch(&g, 1, sw);
	correrRMBC(&g, 1, rm);

	DestruccionDelGrafo(g);
	return 0;
}