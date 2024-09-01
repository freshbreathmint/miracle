#include "containers/dynamic_array.h"

#include <stdlib.h> // malloc & free
#include <string.h> // memcpy

void* dynamic_array_init(size_t capacity, size_t stride){
    // Calculate the size of the header and the data.
    size_t header_size = ARRAY_FIELDS * sizeof(size_t);
    size_t data_size = capacity * stride;

    // Allocate the memory for the dynamic array.
    size_t *dynamic_array = malloc(header_size + data_size);
    
    // Initialize the header.
    dynamic_array[ARRAY_CAPACITY] = capacity;   // Number of elements that can be held.
    dynamic_array[ARRAY_LENGTH] = 0;            // Number of elements in the array.
    dynamic_array[ARRAY_STRIDE] = stride;       // Size of each element in bytes.

    // Return a pointer to the data section, skipping the header.
    return (void*)(dynamic_array + ARRAY_FIELDS);
}

void dynamic_array_free(void* array){
    if(array){
        // Get the position of the header.
        size_t *header = (size_t*)array - ARRAY_FIELDS;

        // Free the array starting from the header.
        free(header);
    }
}

size_t dynamic_array_get_field(void* array, size_t field){
    // Get the position of the header.
    size_t *header = (size_t*)array - ARRAY_FIELDS;

    // Return the value of the field.
    return header[field];
}

void dynamic_array_set_field(void* array, size_t field, size_t value){
    // Get the position of the header.
    size_t *header = (size_t*)array - ARRAY_FIELDS;

    // Set the value of the specified field.
    header[field] = value;
}

void* dynamic_array_resize(void* array){
    // Get the header values.
    size_t capacity = array_capacity(array);
    size_t length = array_length(array);
    size_t stride = array_stride(array);

    // Create a new array with double the capacity.
    void* new_array = dynamic_array_init(capacity * 2, stride);

    // Copy the existing elements to the new array and set the length
    memcpy(new_array, array, length * stride);
    array_set_length(new_array, length);

    // Free the old array and return the new one.
    array_free(array);
    return new_array;
}

//TODO: Rest of the array functions