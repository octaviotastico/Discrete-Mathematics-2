#include "time.h"
#include "checks.h"

double c(clock_t s, clock_t t) {
    double r = (double)(t - s) / CLOCKS_PER_SEC;
    return r;
}

int main(int argc, char *argv[]) {

    if(argc < 3) return -1;

	u32 sw = atoi(argv[1]);
	u32 rm = atoi(argv[2]);

    clock_t s, t, gs, gt;

    gs = s = clock();
	Grafo g = ConstruccionDelGrafo();
	t = clock();
    fprintf(stdout, "%fs\n", c(s, t));

    s = clock();
	correrNatural(&g, 1);
    t = clock();
    fprintf(stdout, "%fs\n", c(s, t));

    s = clock();
	correrWelsh(&g, 1);
    t = clock();
    fprintf(stdout, "%fs\n", c(s, t));
	
    s = clock();
    correrSwitch(&g, 1, sw);
    t = clock();
    fprintf(stdout, "%fs\n", c(s, t));
	
    s = clock();
    correrRMBC(&g, 1, rm);
    t = clock();
    fprintf(stdout, "%fs\n", c(s, t));

    s = clock();
    correrBipartito(&g, 1);
    t = clock();
    fprintf(stdout, "%fs\n", c(s, t));
    
    s = clock();
	DestruccionDelGrafo(g);
	t = clock();
    fprintf(stdout, "%fs\n", c(s, t));

    gt = clock();
    fprintf(stdout, "%fs\n", c(gs, gt));
    return 0;
}