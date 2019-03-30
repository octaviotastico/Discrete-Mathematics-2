BDIR := bin
IDIR := Wahlaan
LDIR := tests/lib
ODIR := obj
TDIR := tests

VPATH = $(IDIR):$(TDIR):$(LDIR)

INPUT = ""
OUTPUT = ""

SWITCH = 0
RMBC = 0

CC := gcc
CFLAGS := -g -I$(IDIR) -I$(LDIR) -Wall -Wextra -O3 -std=c99

# Headers
LIB = Rii.h grafo.h map.h tree.h vector.h checks.h

# Objects
_OBJ = color.o grafo.o map.o memory.o order.o query.o tree.o vector.o checks.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/%: $(ODIR)/%.o $(OBJ) $(LIB)
	@$(CC) -o $@ $^ $(CFLAGS)

penazzi: $(BDIR)/penazzi
	@./$(BDIR)/penazzi $(SWITCH) $(RMBC) <$(INPUT) >$(OUTPUT)

%.v: $(BDIR)/%
	@valgrind --show-reachable=yes --leak-check=full $(BDIR)/$(subst .v,,$@)

.PRECIOUS: $(ODIR)/%.o

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/*