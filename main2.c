#include "Rii.h"
#include "time.h"

clock_t total(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {

    clock_t start_t, end_t;

    start_t = clock();
	Grafo g = ConstruccionDelGrafo();
    end_t = clock();

    printf("Time spent creating Graph: %ld\n", total(start_t, end_t));

    start_t = clock();
    Bipartito(g);
    end_t = clock();

    printf("Time spent running Bipartito: %ld\n", total(start_t, end_t));
    printf("X(G) = %u\n", NumeroDeColores(g));

    start_t = clock();
    Greedy(g);
    end_t = clock();

    printf("Time spent running Greedy: %ld\n", total(start_t, end_t));
    printf("X(G) = %u\n", NumeroDeColores(g));

	return 0;
}

/*

gcc -g -IWahlaan -Wall -Wextra -O3 -std=c99 -o ej main2.c Wahlaan/vector.c Wahlaan/map.c Wahlaan/order.c Wahlaan/tree.c Wahlaan/grafo.c Wahlaan/query.c Wahlaan/memory.c Wahlaan/color.c

./ej < new\ test

*/