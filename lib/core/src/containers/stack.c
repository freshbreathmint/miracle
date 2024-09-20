#include "containers/stack.h"

#include <stdlib.h>
#include <string.h>

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
        //TODO: Error msg
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
        //TODO: Error msg
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

bool stack_push(Stack *s, const void* element){
    if(!s || !element){
        // Invalid stack or element.
        //TODO: Error msg
        return false;
    }

    // Ensure there's space for the new element.
    if(!_stack_ensure_allocated(s, s->element_count + 1)){
        return false;
    }

    // Calculate the address where the new element should be placed.
    void* target = (char*)s->memory + (s->element_count * s->element_size);
    memcpy(target, element, s->element_size);
    s->element_count++;
    return true; 
}

bool stack_pop(Stack *s, void* out_element){
    if(!s || s->element_count == 0 || !out_element){
        // Invalid use
        //TODO: Error msg
        return false;
    }

    s->element_count--;
    void* source = (char*)s->memory + (s->element_count * s->element_size);
    memcpy(out_element, source, s->element_size);
    return true;
}

bool stack_peek(const Stack *s, void* out_element){
    if(!s || s->element_count == 0 || !out_element){
        // Invalid stack or no elements
        //TODO: Error msg
        return false;
    }

    void* source = (char*)s->memory + ((s->element_count - 1) * s->element_size);
    memcpy(out_element, source, s->element_size);
    return true;
}