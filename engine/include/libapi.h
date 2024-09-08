#pragma once

#include "engine.h" //for the functions

#include "containers/dynamic_array.h"

void** gen_funcs(){
    // Create function pointer array.
    void** funcs = array(void*);

    funcs = array_push(void*, funcs, &(void*){(void*)funcA});
    funcs = array_push(void*, funcs, &(void*){(void*)funcB});

    // Return the array.
    return funcs;
}