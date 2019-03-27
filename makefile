BDIR := bin
IDIR := Wahlaan
LDIR := tests/lib
ODIR := obj
TDIR := tests

VPATH = $(IDIR):$(TDIR)

CC := gcc
CFLAGS := -g -I$(IDIR) -I$(LDIR) -Wall -Wextra -O3 -std=c99

_LIB = order_check.c
LIB = $(patsubst %, $(LDIR)/%, $(_LIB))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/%: $(ODIR)/%.o $(LIB)
	$(CC) -o $@ $^ $(CFLAGS) $(IDIR)/*.c

penazzi: $(BDIR)/penazzi
	./$(BDIR)/penazzi

tests: $(BDIR)/tests
	./$(BDIR)/tests

%.v: $(BDIR)/%
	valgrind --show-reachable=yes --leak-check=full $(BDIR)/$(subst .v,,$@)

.PRECIOUS: $(ODIR)/%.o

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/*