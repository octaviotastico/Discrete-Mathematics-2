#include "checks.h"

void properColoring(Grafo g, u32 x) {
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

void checkIsomorfism(Grafo a, Grafo b) {
	u32 n1 = NumeroDeVertices(a), n2 = NumeroDeVertices(b);
	assert(n1 == n2);
	assert(NumeroDeLados(a) == NumeroDeLados(b));
	assert(NumeroDeColores(a) == NumeroDeColores(b));
	fore(i, 0, n1) {
		assert(NombreDelVertice(a, i) == NombreDelVertice(b, i));
		assert(ColorDelVertice(a, i) == ColorDelVertice(b, i));
		assert(GradoDelVertice(a, i) == GradoDelVertice(b, i));
		fore(j, 0, GradoDelVertice(a, i)) {
			assert(NombreJotaesimoVecino(a, i, j) == NombreJotaesimoVecino(b, i, j));
			assert(ColorJotaesimoVecino(a, i, j) == ColorJotaesimoVecino(b, i, j));
		}
	}
}

void checkNatural(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // First vertex
	u32 ant = NombreDelVertice(g, 0);
	fore(i, 1, n) {
		u32 v = NombreDelVertice(g, i);
        // Check if a[i] < a[i + 1]
		assert(ant < v);
		ant = v;
	}
}

void checkWelsh(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // Degree of first vertex
	u32 ant = GradoDelVertice(g, 0);
	fore(i, 1, n) {
		u32 v = GradoDelVertice(g, i);
        // Check that d(a[i]) >= d(a[i + 1])
		assert(ant >= v);
		ant = v;
	}
}

void chechRMBC(Grafo g) {
	u32 n = NumeroDeVertices(g);
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
}

void checkRMBCr(Grafo g) {
	u32 n = NumeroDeVertices(g);
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
}

void checkRMBCc(Grafo g) {
	u32 n = NumeroDeVertices(g);
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
}

void correrNatural(Grafo* g, u32 n) {
	fore(i, 0, n) {
		OrdenNatural(g[i]);
		#ifdef HARD
		checkNatural(g[i]);
		properColoring(g[i], NumeroDeColores(g[i]));
		fore(j, 0, n) fore(k, i + 1, n) checkIsomorfism(g[j], g[k]);
		#endif
	}
	if(n == 1) fprintf(stdout, "%u\n", NumeroDeColores(g[0]));
}

void correrWelsh(Grafo* g, u32 n) {
	fore(i, 0, n) {
		OrdenWelshPowell(g[i]);
		Greedy(g[i]);
		#ifdef HARD
		checkWelsh(g[i]);
		properColoring(g[i], NumeroDeColores(g[i]));
		fore(i, 0, n) fore(j, i + 1, n) checkIsomorfism(g[i], g[j]);
		#endif
	}
	if(n == 1) fprintf(stdout, "%u\n", NumeroDeColores(g[0]));
}

void correrSwitch(Grafo* g, u32 n, u32 times) {
	u32 x = NumeroDeColores(g[0]);
	fore(i, 0, times) {
		int index = rand() % n;
		u32 N = NumeroDeVertices(g[index]);
		int r1 = rand() % N;
		int r2 = rand() % N;
		SwitchVertices(g[index], r1, r2);
		Greedy(g[index]);
		#ifdef HARD
		properColoring(g[index], NumeroDeColores(g[index]));
		#endif
		x = min(x, NumeroDeColores(g[index]));
	}
	if(n == 1) fprintf(stdout, "%u\n", x);
}

void correrRMBC(Grafo* g, u32 n, u32 times) {
	u32 x = NumeroDeColores(g[0]);
	fore(i, 0, times) {
		int index = rand() % n;
		int r = rand() % 3;
		switch(r) {
			case 0:
				RMBCnormal(g[index]);
				#ifdef HARD
				chechRMBC(g[index]);
				#endif
				break;
			case 1:
				RMBCrevierte(g[index]);
				#ifdef HARD
				checkRMBCr(g[index]);
				#endif
				break;
			case 2:
				RMBCchicogrande(g[index]);
				#ifdef HARD
				checkRMBCc(g[index]);
				#endif
				break;
		}
		Greedy(g[index]);
		#ifdef HARD
		properColoring(g[index], NumeroDeColores(g[index]));
		#endif
		assert(NumeroDeColores(g[index]) <= x);
		x = NumeroDeColores(g[index]);
	}
	fprintf(stdout, "%u\n", x);
}

void correrBipartito(Grafo* g, u32 n) {
	int bip = 0;
	fore(i, 0, n) {
		bip = Bipartito(g[i]);
		#ifdef HARD
		properColoring(g[i], NumeroDeColores(g[i]));
		#endif
	}

	if(n == 1 && bip) fprintf(stdout, "Yes\n");
	else if(n == 1 && !bip) fprintf(stdout, "No\n");
}
