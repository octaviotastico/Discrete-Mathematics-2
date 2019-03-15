#include "vector.h"

struct Vector {
    int* array;
    size_t size;
    size_t capacity;
};

static void vector_resize(vector v, size_t cap) {
    v->array = (int*)realloc(v->array, cap * sizeof(int));
}

vector vector_init() {
    vector v = (vector)malloc(sizeof(struct Vector));
    v->array = NULL;
    v->size = 0;
    v->capacity = 0;
}

void vector_push_back(vector v, int x) {
    assert(v != NULL);
    if(v->size == v->capacity) {
        if(!v->capacity) v->capacity++;
        else v->capacity *= 2;

        vector_resize(v, v->capacity);
    }
    v->array[v->size++] = x;
}

void vector_pop_back(vector v) {
    assert(v != NULL);
    v->size--;
    if(2 * v->size == v->capacity) {
        v->capacity /= 2;
        vector_resize(v, v->capacity);
    }
}

int vector_at(vector v, int i) {
    assert(v != NULL);
    assert(0 <= i && i < v->size);
    return v->array[i];
}

void vector_swap(vector v, int i, int j) {
    assert(v != NULL);
    assert(0 <= i && i < v->size);
    assert(0 <= j && j < v->size);
    if(i == j) return;
    v->array[i] ^= v->array[j];
    v->array[j] ^= v->array[i];
    v->array[i] ^= v->array[j];
}

void vector_shuffle(vector v) {

}

void vector_sort(vector v, bool comp(int, int)) {

}

bool vector_empty(vector v) {
    assert(v != NULL);
    return v->size == 0;
}

void vector_clear(vector v) {
    assert(v != NULL);
    free(v->array);
    v->size = 0;
    v->capacity = 0;
}

void vector_destroy(vector v) {
    assert(v != NULL);
    vector_clear(v);
    free(v); v = NULL;
}

size_t vector_size(vector v) {
    assert(v != NULL);
    return v->size;
}

size_t vector_capacity(vector v) {
    assert(v != NULL);
    return v->capacity;
}

