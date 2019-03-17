#include "Rii.h"

void checkNatural(Grafo g) {
	OrdenNatural(g);
	u32 n = NumeroDeVertices(g);
	u32 ant = NombreDelVertice(g, 0);;
	fore(i, 1, n) {
		u32 v = NombreDelVertice(g, i);
		assert(ant < v);
		ant = v;
	}
}

void checkWelsh(Grafo g) {
	OrdenWelshPowell(g);
	u32 n = NumeroDeVertices(g);
	u32 ant = GradoDelVertice(g, 0);;
	fore(i, 1, n) {
		u32 v = GradoDelVertice(g, i);
		assert(ant >= v);
		ant = v;
	}
}

void checkRMBC(Grafo g) {
	RMBCnormal(g);
	u32 n = NumeroDeVertices(g);
	u32 c = 0;
	fore(i, 1, n) {
		int x = ColorDelVertice(g, i);
		if(x == c + 1) c = x;
		assert(x == c);
	}
	assert(c + 1 == NumeroDeColores(g));
}

void checkRMBCr(Grafo g) {
	RMBCrevierte(g);
	u32 n = NumeroDeVertices(g);
	u32 c = NumeroDeColores(g) - 1;
	fore(i, 1, n) {
		int x = ColorDelVertice(g, i);
		if(x == c - 1) c = x;
		assert(x == c);
	}
	assert(c == 0);
}

void checkRMBCc(Grafo g) {
	RMBCchicogrande(g);
	u32 n = NumeroDeVertices(g);
	int* arr = calloc(n, sizeof(int));
	u32 c = ColorDelVertice(g, 0);
	u32 a = 0;
	u32 b = 1;
	u32 d = 1;
	fore(i, 1, n) {
		int x = ColorDelVertice(g, i);
		if(x != c) {
			d++;
			assert(!arr[x]);
			arr[x] = 1;
			assert(a <= b);
			a = b;
			b = 0;
			c = x;
		}
		b++;
	}
	assert(d == NumeroDeColores(g));
}

int main() {
	// We will hold the edges here (just to check that nothing breaks)
	map m = map_create();

	Grafo g = ConstruccionDelGrafo(m);

	int tests[5][5] = {{0, 0, 0, 0, 0},
					   {0, 0, 0, 0, 0},
					   {0, 0, 0, 0, 0},
					   {0, 0, 0, 0, 0},
					   {0, 0, 0, 0, 0}};

	int pr = 0;

	fore(_, 0, 1000) {
		int r = rand() % 5;
		switch(r) {
			case 0:
				checkNatural(g);
			case 1:
				checkWelsh(g);
			case 2:
				checkRMBC(g);
			case 3:
				checkRMBCr(g);
			case 4:
				checkRMBCc(g);
		}
		tests[pr][r]++;
		pr = r;
		Greedy(g);
	}

	fore(i, 0, 5) {
		fore(j, 0, 5) {
			printf("%d ", tests[i][j]);
		} printf("\n");
	}


	
	return 0;
}