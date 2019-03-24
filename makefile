IDIR := Wahlaan
ODIR := obj
BDIR := bin
TDIR := tests

VPATH = $(IDIR):$(TDIR)

CC := gcc
CFLAGS := -g -I$(IDIR) -Wall -Wextra -O3 -std=c99

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/%: $(ODIR)/%.o $(ODIR)/order_check.o
	$(CC) -o $@ $^ $(CFLAGS) $(IDIR)/*.c

general: $(BDIR)/test
	./$(BDIR)/test

%.v: $(BDIR)/%
	valgrind --show-reachable=yes --leak-check=full $(BDIR)/$(subst .valgrind,,$@)

.PRECIOUS: $(ODIR)/%.o

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/*