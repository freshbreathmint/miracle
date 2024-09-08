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

void* dynamic_array_push(void* array, const void* value_ptr){
    // Get the header values.
    size_t capacity = array_capacity(array);
    size_t length = array_length(array);
    size_t stride = array_stride(array);

    // Resize array if needed.
    if(length >= capacity){
        array = array_resize(typeof(array), array);
    }

    // Find a place for the new element
    size_t address = (size_t)array + (length * stride);

    // Copy the new element into the array and update the length.
    memcpy((void*)address, value_ptr, stride);
    array_set_length(array, length + 1);

    // Return the modified array.
    return array;
}

void dynamic_array_pop(void* array, void* dest){
    // Get the header values.
    size_t length = array_length(array);
    size_t stride = array_stride(array);

    // Get the location of the last element.
    size_t address = (size_t)array;
    address += ((length -1) * stride);

    // Copy the last element to the destination and decrement the length.
    memcpy(dest, (void*)address, stride);
    array_set_length(array, length - 1);
}

void* dynamic_array_pop_at(void* array, size_t index, void* dest){
    // Get the header values.
    size_t length = array_length(array);
    size_t stride = array_stride(array);

    // Check if the index is out of bounds.
    if(index >= length){
        //TODO: Some sort of error message
        return array; // Return the array, unmodified.
    }

    // Get the location of the index and copy the element into the destination buffer.
    size_t address = (size_t)array;
    memcpy(dest, (void*)(address + (index * stride)), stride);

    // If we weren't targeting the last element, snip out the entry and copy the rest inward.
    if(index != length - 1){
        memcpy(
            (void*)(address + (index * stride)),        // Address of the element being removed.
            (void*)(address + ((index +1) * stride)),   // Address of the element immediately following.
            stride * (length - index - 1));             // Total number of bytes to copy.
    }

    // Decrement the length and return the array.
    array_set_length(array, length - 1);
    return array;
}

void* dynamic_array_insert_at(void* array, size_t index, void* element){
    // Get the header values.
    size_t capacity = array_capacity(array);
    size_t length = array_length(array);
    size_t stride = array_stride(array);

    // Check if the index is out of bounds.
    if(index >= length){
        //TODO: Some sort of error message
        return array; // Return the array, unmodified.
    }

    // Resize the array if it's already full.
    if(length >= capacity){
        array = array_resize(typeof(array), array);
    }

    // Get the address and push elements from index forward out by one.
    size_t address = (size_t)array;
    memcpy(
            (void*)(address + ((index + 1) * stride)),  // Address right after the index, insertion point. 
            (void*)(address + (index * stride)),        // Index address
            stride * (length - index));                 // Number of elements to be shifted.
    
    // Set the value at the index.
    memcpy((void*)(address + (index * stride)), element, stride);

    // Increase the length and return the array.
    array_set_length(array, length + 1);
    return array;
}