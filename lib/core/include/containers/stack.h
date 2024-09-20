#pragma once

// Stack
/**
 * @brief A simple stack container for arbitrary data types.
 * 
 * Operates in a "Last In, First Out" (LIFO) manner, like a stack of plates.
 * Elements are added (pushed) onto the top and removed (popped) from the top.
 * 
 * @param element_size  The size of each element in bytes.
 * @param element_count The current number of elements on the stack.
 * @param allocated     The total amount of memory allocated for the stack.
 * @param memory        Pointer to the memory block containing the elements.
 */
typedef struct Stack {
    unsigned int    element_size;
    unsigned int    element_count;
    unsigned int    allocated;
    void*           memory;
} Stack;

Stack* stack_create(unsigned int element_size);