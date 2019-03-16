#ifndef VECTOR
#define VECTOR

#include "defs.h"

typedef struct Vector* vector;

vector vector_create();

void vector_push_back(vector, u32);

void vector_pop_back(vector);

u32 vector_at(vector, int);

void vector_set_at(vector v, int i, u32 x);

int vector_empty(vector);

void vector_clear(vector);

void vector_destroy(vector);

size_t vector_size(vector);

size_t vector_capacity(vector);

#endif