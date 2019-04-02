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

void doNatural(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // Natural order
	OrdenNatural(g);
	#ifdef HARD
    // First vertex
	u32 ant = NombreDelVertice(g, 0);
	fore(i, 1, n) {
		u32 v = NombreDelVertice(g, i);
        // Check if a[i] < a[i + 1]
		assert(ant < v);
		ant = v;
	}
	#endif
}

void doWelsh(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // Welsh order
	OrdenWelshPowell(g);
	#ifdef HARD
    // Degree of first vertex
	u32 ant = GradoDelVertice(g, 0);
	fore(i, 1, n) {
		u32 v = GradoDelVertice(g, i);
        // Check that d(a[i]) >= d(a[i + 1])
		assert(ant >= v);
		ant = v;
	}
	#endif
}

void doRMBC(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // RMBC order
	RMBCnormal(g);
	#ifdef HARD
    // Current color
	u32 c = ColorDelVertice(g, 0);
    // Must be zero
    assert(c == 0);
	fore(i, 1, n) {
		u32 x = ColorDelVertice(g, i);
        // Next color = current color + 1
		if(x == c + 1) c = x;
        // Check the above
		assert(x == c);
	}
    // Using every color?
	assert(c + 1 == NumeroDeColores(g));
	#endif
}

void doRMBCr(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // RMBC-reverse order
	RMBCrevierte(g);
	#ifdef HARD
    // Current color
	u32 c = ColorDelVertice(g, 0);
    // Must be the last possible color
	assert(c + 1 == NumeroDeColores(g));
	fore(i, 1, n) {
		u32 x = ColorDelVertice(g, i);
        // Next color = current color + 1
		if(x == c - 1) c = x;
        // Check the above
		assert(x == c);
	}
    // Using every color?
	assert(c == 0);
	#endif
}

void doRMBCc(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // RMBC-by-size order
	RMBCchicogrande(g);
	#ifdef HARD
    // Array to track used colors
	int* arr = calloc(n, sizeof(int));
    // Current color
	u32 c = ColorDelVertice(g, 0);
    // How many verteces of current color
	u32 Vi = 1;
    // How many verteces of previous color
	u32 Vj = 0;
    // Total colors used
	u32 d = 1;
	fore(i, 1, n) {
		u32 x = ColorDelVertice(g, i);
		if(x != c) {
            // Check if new color has already appeared
			assert(arr[x] == 0);
            // Mark this color as used
			arr[x] = 1;
            // Check |Vj| <= |Vi|
			assert(Vj <= Vi);
            // Previous color count = current color count
			Vj = Vi;
            // New color
			c = x;
			d++;
            // New count for new color
			Vi = 0;
		}
		Vi++;
	}
    free(arr);
	assert(d == NumeroDeColores(g));
	#endif
}

static void properColoring(Grafo g, u32 x) {
    u32 n = NumeroDeVertices(g);
    u32 y = 0;
    fore(i, 0, n) {
        u32 d = GradoDelVertice(g, i);
        u32 c = ColorDelVertice(g, i);
        y = max(y, c);
        fore(j, 0, d) {
            assert(ColorJotaesimoVecino(g, i, j) != c);
        }
    }
    assert(y + 1 == x);
}

void doGreedy(Grafo g) {
    // Greedy
    Greedy(g);
    // Check correct coloring
	#ifdef HARD
    properColoring(g, NumeroDeColores(g));
	#endif
}

void doBipartito(Grafo g) {
    // Bipartito
    Bipartito(g);
    // Check correct coloring
    #ifdef HARD
	properColoring(g, NumeroDeColores(g));
	#endif
}
