#include "order_check.h"

int doNatural(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // Natural order
	OrdenNatural(g);
    // First vertex
	u32 ant = NombreDelVertice(g, 0);
	fore(i, 1, n) {
		u32 v = NombreDelVertice(g, i);
        // Check if a[i] < a[i + 1]
		if(v <= ant) return 1;
		ant = v;
	}
    return 0;
}

int doWelsh(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // Welsh order
	OrdenWelshPowell(g);
    // Degree of first vertex
	u32 ant = GradoDelVertice(g, 0);
	fore(i, 1, n) {
		u32 v = GradoDelVertice(g, i);
        // Check that d(a[i]) >= d(a[i + 1])
		if(ant < v) return 1;
		ant = v;
	}
    return 0;
}

int doRMBC(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // RMBC order
	RMBCnormal(g);
    // Current color
	u32 c = ColorDelVertice(g, 0);
    // Must be zero
    if(c != 0) return 1;
	fore(i, 1, n) {
		u32 x = ColorDelVertice(g, i);
        // Next color = current color + 1
		if(x == c + 1) c = x;
        // Check the above
		if(x != c) return 1;
	}
    // Using every color?
    if(c + 1 != NumeroDeColores(g)) return 1;

    return 0;
}

int doRMBCr(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // RMBC-reverse order
	RMBCrevierte(g);
    // Current color
	u32 c = ColorDelVertice(g, 0);
    // Must be the last possible color
    if(c + 1 != NumeroDeColores(g)) return 1;
	fore(i, 1, n) {
		u32 x = ColorDelVertice(g, i);
        // Next color = current color + 1
		if(x == c - 1) c = x;
        // Check the above
		if(x != c) return 1;
	}
    // Using every color?
	if(c != 0) return 1;

    return 0;
}

int doRMBCc(Grafo g) {
	u32 n = NumeroDeVertices(g);
    // RMBC-by-size order
	RMBCchicogrande(g);
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
			if(arr[x] == 1) {
                free(arr);
                return 1;
            }
            // Mark this color as used
			arr[x] = 1;
            // Check |Vi| <= |Vj|
			if(Vi < Vj) {
                free(arr);
                return 1;
            }
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
	if(d != NumeroDeColores(g)) return 1;
	return 0;
}
