#pragma once

#include "engine.h" //for the function
#include <stdio.h> //remove this

#include "containers/dynamic_array.h"

void** gen_funcs(){
    // Create function pointer array.
    void** funcs = array(void*);

    printf("Array length: %zu\n", array_length(funcs));
    printf("Array capacity: %zu\n", array_capacity(funcs));
    printf("Array stride: %zu\n", array_stride(funcs));
    printf("Address of funcA: %p\n", (void*)funcA);
    printf("Sizeof FuncA: %zu\n", sizeof((void*)funcA));
    printf("Address of funcA stored in funcs[0]: %p\n", (void*)funcs[0]);
    printf("Sizeof FuncA in func[0]: %zu\n", sizeof((void*)funcs[0]));

    funcs = array_push(void*, funcs, funcA);
    funcs = array_push(void*, funcs, funcB);
    printf("pushing...\n");

    printf("Array length: %zu\n", array_length(funcs));
    printf("Array capacity: %zu\n", array_capacity(funcs));
    printf("Array stride: %zu\n", array_stride(funcs));
    printf("Address of funcA: %p\n", (void*)funcA);
    printf("Sizeof FuncA: %zu\n", sizeof((void*)funcA));
    printf("Address of funcA stored in funcs[0]: %p\n", (void*)funcs[0]);
    printf("Sizeof FuncA in func[0]: %zu\n", sizeof((void*)funcs[0]));

    // Return the array.
    return funcs;
}