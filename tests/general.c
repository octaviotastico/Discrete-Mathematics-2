#include "order_check.h"

int main(int argc, char **argv) {

	u32 iterations = 1000;

	if(argc != 2) {
		// printf("Usage: ./test number_of_iterations\n");
		// exit(1);
	} else {
		iterations = atoi(argv[1]);
	}

	Grafo g = ConstruccionDelGrafo();

	printf("Grafo creado\n");
	
	fore(i, 0, iterations) {
		int r = rand() % 5;
		switch(r) {
			case 0:
				if(doNatural(g)) {
					printf("Natural order went wrong\n");
					exit(1);
				}
				break;
			case 1:
				if(doWelsh(g)) {
					printf("Welsh Powell order went wrong\n");
					exit(1);
				}
				break;
			case 2:
				if(doRMBC(g)) {
					printf("RMBC order went wrong\n");
					exit(1);
				}
				break;
			case 3:
				if(doRMBCr(g)) {
					printf("RMBC-reverse order went wrong\n");
					exit(1);
				}
				break;
			case 4:
				if(doRMBCc(g)) {
					printf("RMBC-by-size order went wrong\n");
					exit(1);
				}
				break;
		}
		Greedy(g);
		printf("Current progress: %u\n", i + 1);
	}

	DestruccionDelGrafo(g);

	return 0;
}