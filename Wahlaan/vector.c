#include "vector.h"

struct Vector {
    u32* array;
    size_t size, capacity;
};

static void vector_resize(vector v, size_t cap) {
    v->array = (u32*)realloc(v->array, cap * sizeof(u32));
}

vector vector_create() {
    vector v = (vector)malloc(sizeof(struct Vector));
    v->array = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

int vector_push_back(vector v, u32 x) {
    assert(v != NULL);
    if(v->size == v->capacity) {
        if(!v->capacity) v->capacity++;
        else v->capacity *= 2;

        vector_resize(v, v->capacity);
        if(!v->array) return -1;
    }
    v->array[v->size++] = x;
    return 0;
}

u32 vector_pop_back(vector v) {
    assert(v != NULL && 0 < v->size);
    return v->array[--v->size];
}

u32 vector_at(vector v, u32 i) {
    assert(v != NULL && i < v->size);
    return v->array[i];
}

u32 vector_empty(vector v) {
    assert(v != NULL);
    return v->size == 0;
}

void vector_clear(vector v) {
    assert(v != NULL);
    v->size = 0;
    v->capacity = 0;
    free(v->array);
    v->array = NULL;
}

void vector_destroy(vector v) {
    assert(v != NULL);
    vector_clear(v);
    free(v);
}

size_t vector_size(vector v) {
    assert(v != NULL);
    return v->size;
}

size_t vector_capacity(vector v) {
    assert(v != NULL);
    return v->capacity;
}

