#include "time.h"
#include "checks.h"

float c(clock_t s, clock_t t) {
    float r = (t - s) / CLOCKS_PER_SEC;
    return r;
}

int main() {

    clock_t s, t;

    s = clock();
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
    correrSwitch(g, 1);
    t = clock();
    fprintf(stdout, "%f\n", c(s, t));
	
    s = clock();
    correrRMBC(g, 1);
    t = clock();
    fprintf(stdout, "%f\n", c(s, t));

	DestruccionDelGrafo(g);
	return 0;
}