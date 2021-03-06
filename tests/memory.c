#include "time.h"
#include "checks.h"

int main(int argc, char *argv[]) {

    if(argc < 4) return -1;

	u32 n = atoi(argv[1]);
	u32 sw = atoi(argv[2]);
    u32 rm = atoi(argv[3]);

    Grafo* grafos = (Grafo*)malloc(n * sizeof(Grafo));

    grafos[0] = ConstruccionDelGrafo();

    fore(i, 1, n) {
        grafos[i] = CopiarGrafo(grafos[i - 1]);
    }

    correrNatural(grafos, n);
    correrWelsh(grafos, n);
    correrSwitch(grafos, n, sw);
    correrRMBC(grafos, n, rm);
    correrBipartito(grafos, n);

    fore(i, 0, n) DestruccionDelGrafo(grafos[i]);

    free(grafos);

    return 0;
}