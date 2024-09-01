#include <stddef.h>

#define ARRAY_DEFAULT_CAPACITY 1

#define array(T) (T *)dynamic_array_init(ARRAY_DEFAULT_CAPACITY, sizeof(T))
#define array_reserve(capacity, T) (T *)dynamic_array_init(capacity, sizeof(T))

#define array_free(array_p) dynamic_array_free(array_p)

#define array_capacity(array_p) dynamic_array_get_field(array_p, ARRAY_CAPACITY)
#define array_length(array_p) dynamic_array_get_field(array_p, ARRAY_LENGTH)
#define array_stride(array_p) dynamic_array_get_field(array_p, ARRAY_STRIDE)

#define array_clear(array_p) dynamic_array_set_field(array_p, ARRAY_LENGTH, 0)
#define array_set_length(array_p, value) dynamic_array_set_field(array_p, ARRAY_LENGTH, value)

#define array_resize(T, array_p) (T *)dynamic_array_resize((void *)(array_p))

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