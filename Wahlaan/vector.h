#ifndef VECTOR
#define VECTOR

#include "Rii.h"

// Pointer to Vector structure
typedef struct Vector * vector;

// Creates a new vector
vector vector_create();

// Push a new element. Resize if it's necessary
u32 vector_push_back(vector, u32);

// Deletes the last added element
u32 vector_pop_back(vector);

// Returns the elem of the vector in the given position
u32 vector_at(vector, u32);

// Returns 1 if vector is empty, otherwise 0
u32 vector_empty(vector);

// Removes all elements from vector
void vector_clear(vector);

// Removes all elements from vector and destroy it
void vector_destroy(vector);

// Returns size of a given vector
size_t vector_size(vector);

// Returns max capacity of given vector
size_t vector_capacity(vector);

#endif