#include "containers/stack.h"

#include <stdlib.h>

static bool _stack_ensure_allocated(Stack *s, unsigned int min_capacity){
    if(s->allocated >= s->element_size * min_capacity){
        // Current allocation is sufficient.
        return true;
    }

    // Determine new allocation (double the current or min_capacity)
    unsigned int new_allocated = s->allocated ? s->allocated * 2 : s->element_size *  min_capacity;
    if(new_allocated < s->element_size * min_capacity){
        new_allocated = s->element_size * min_capacity;
    }

    // Allocate new memory block.
    void* new_memory = realloc(s->memory, new_allocated);
    if(!new_memory){
        // Allocation failed.
        //TODO: Some sort of error message
        return false;
    }

    // Update the stack with new memory and capacity.
    s->memory = new_memory;
    s->allocated = new_allocated;
    return true;
}

bool stack_create(Stack *s, unsigned int element_size){
    // Make sure it's a valid stack.
    if(!s){
        //TODO: Some sort of error message
        return false;
    }

    // Initialize the stack.
    s->element_size = element_size;
    s->element_count = 0;
    s->allocated = 0;
    s->memory = NULL;

    // Allocate the memory block with minimum capacity of 4.
    if(!_stack_ensure_allocated(s, 4)){
        return false;
    }
    return true;
}

void stack_destroy(Stack *s){
    if(!s){
        return;
    }

    free(s->memory);
    s->memory = NULL;
    s->allocated = 0;
    s->element_count = 0;
    s->element_size = 0;
}