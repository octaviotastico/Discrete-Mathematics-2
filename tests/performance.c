#include "time.h"
#include "checks.h"

double c(clock_t s, clock_t t) {
    double r = (t - s) / CLOCKS_PER_SEC;
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
    fprintf(stdout, "%f\n", c(s, t));

    s = clock();
	correrNatural(g);
    t = clock();
    fprintf(stdout, "%f\n", c(s, t));

    s = clock();
	correrWelsh(g);
    t = clock();
    fprintf(stdout, "%f\n", c(s, t));
	
    s = clock();
    correrSwitch(g, sw);
    t = clock();
    fprintf(stdout, "%f\n", c(s, t));
	
    s = clock();
    correrRMBC(g, rm);
    t = clock();
    fprintf(stdout, "%f\n", c(s, t));

    s = clock();
	DestruccionDelGrafo(g);
	t = clock();
    fprintf(stdout, "%f\n", c(s, t));

    gt = clock();
    fprintf(stdout, "%f\n", c(gs, gt));
    return 0;
}