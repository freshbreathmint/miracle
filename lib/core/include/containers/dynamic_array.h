#pragma once

#include <stddef.h>

#define ARRAY_DEFAULT_CAPACITY 1

#define array(T) (T*)dynamic_array_init(ARRAY_DEFAULT_CAPACITY, sizeof(T))
#define array_reserve(capacity, T) (T*)dynamic_array_init(capacity, sizeof(T))

#define array_free(array_ptr) dynamic_array_free(array_ptr)

#define array_capacity(array_ptr) dynamic_array_get_field(array_ptr, ARRAY_CAPACITY)
#define array_length(array_ptr) dynamic_array_get_field(array_ptr, ARRAY_LENGTH)
#define array_stride(array_ptr) dynamic_array_get_field(array_ptr, ARRAY_STRIDE)

#define array_clear(array_ptr) dynamic_array_set_field(array_ptr, ARRAY_LENGTH, 0)
#define array_set_length(array_ptr, value) dynamic_array_set_field(array_ptr, ARRAY_LENGTH, value)

#define array_resize(T, array_ptr) (T*)dynamic_array_resize(array_ptr)

#define array_push(T, array_ptr, value_ptr) (T*)dynamic_array_push(array_ptr, (const void*)(value_ptr))
#define array_pop(array_ptr, dest) dynamic_array_pop(array_ptr, dest)
#define array_pop_at(T, array_ptr, index, dest) (T*)dynamic_array_pop_at(array_ptr, index, dest)
#define array_insert(T, array_ptr, index, element)                          \
    {                                                                       \
        T temp = element;                                                   \
        array_ptr = (T*)dynamic_array_insert_at(array_ptr, index, &temp);   \
    }                                               

typedef enum dynamic_array_header {
    ARRAY_CAPACITY,
    ARRAY_LENGTH,
    ARRAY_STRIDE,
    ARRAY_FIELDS
} dynamic_array_header;

void* dynamic_array_init(size_t capacity, size_t stride);
void dynamic_array_free(void* array);
size_t dynamic_array_get_field(void* array, size_t field);
void dynamic_array_set_field(void* array, size_t field, size_t value);
void* dynamic_array_resize(void* array);
void* dynamic_array_push(void* array, const void* value_ptr);
void dynamic_array_pop(void* array, void* dest);
void* dynamic_array_pop_at(void* array, size_t index, void* dest);
void* dynamic_array_insert_at(void* array, size_t index, void* element);