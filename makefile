BDIR := bin
IDIR := Wahlaan
LDIR := tests/lib
ODIR := obj
TDIR := tests

VPATH = $(IDIR):$(TDIR):$(LDIR)

CC := gcc

PROTECTION := -g -DNDEBUG -Wshadow -fstack-protector -fsanitize=undefined -fsanitize=signed-integer-overflow
CFLAGS := -I$(IDIR) -I$(LDIR) $(OFLAG) -Wall -Wextra -O3 -std=c99

CFLAGS += $(PROTECTION)

# Headers
_LIB = $(wildcard $(IDIR)/*.h) checks.h
LIB = $(patsubst $(IDIR)/%, %, $(_LIB))

# Objects
_OBJ = $(wildcard $(IDIR)/*.c)
OBJ = $(patsubst $(IDIR)/%.c, $(ODIR)/%.o, $(_OBJ)) $(ODIR)/checks.o

$(ODIR)/%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/%: $(ODIR)/%.o $(OBJ) $(LIB)
	@$(CC) -o $@ $^ $(CFLAGS)

penazzi: $(BDIR)/penazzi
	@$(BDIR)/penazzi $(SWITCH) $(RMBC) <$(INPUT) >$(OUTPUT)

performance: $(BDIR)/performance
	@$(BDIR)/performance $(SWITCH) $(RMBC) <$(INPUT) >$(OUTPUT)

memory: $(BDIR)/memory
	@valgrind --show-reachable=yes --leak-check=full -v --log-file="out/memory/$(notdir $(OUTPUT))" $(BDIR)/$(subst .v,,$@) $(GRAPHS) $(SWITCH) $(RMBC) <$(INPUT) >$(OUTPUT)
%.v: $(BDIR)/%
	@valgrind --show-reachable=yes --leak-check=full -v --log-file="out/memory/$(notdir $(OUTPUT))" $(BDIR)/$(subst .v,,$@) $(SWITCH) $(RMBC) <$(INPUT) >$(OUTPUT)

.PRECIOUS: $(ODIR)/%.o

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o $(BDIR)/*