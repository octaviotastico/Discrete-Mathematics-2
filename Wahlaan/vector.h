#ifndef VECTOR
#define VECTOR

#include "Rii.h"

typedef struct Vector* vector;

vector vector_create();

u32 vector_push_back(vector, u32);

u32 vector_pop_back(vector);

u32 vector_at(vector, u32);

u32 vector_empty(vector);

void vector_clear(vector);

void vector_destroy(vector);

size_t vector_size(vector);

size_t vector_capacity(vector);

#endif