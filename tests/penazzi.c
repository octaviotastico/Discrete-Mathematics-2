#include "checks.h"

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