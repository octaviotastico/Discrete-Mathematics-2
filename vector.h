#include "assert.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Vector* vector;

vector vector_init();

void vector_push_back(vector, int);

void vector_pop_back(vector);

int vector_at(vector, int);

void vector_swap(vector, int, int);

void vector_shuffle(vector);

void vector_sort(vector, bool(int, int));

bool vector_empty(vector);

void vector_clear(vector);

void vector_destroy(vector);

size_t vector_size(vector);

size_t vector_capacity(vector);