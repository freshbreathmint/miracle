#pragma once

#include <stdio.h>
#include "containers/dynamic_array.h"


// Function Info
typedef struct {
    char* library;
    char* name;
    void* address;
    void** func_ptr;
} FuncInfo;

// Unbound Function
void unbound_function(const char *function_name) {
    printf("Tried to call an unbound function: %s\n", function_name);
}

// Function Declaration Macro
#define DECLARE_FUNCTION(type, function, ...)                   \
    type unbound_##function(__VA_ARGS__) {                      \
        unbound_function(#function);                            \
        return (type)0;                                         \
    }                                                           \
    type (*function)(__VA_ARGS__) = unbound_##function;         \
    FuncInfo func_info_##function = {                           \
        .library = NULL,                                        \
        .name = #function,                                      \
        .address = NULL,                                        \
        .func_ptr = (void**)&function                           \
    };

// Import Function Macro
#define IMPORT_FUNCTION(array_ptr, lib, function)                           \
    do {                                                                    \
        func_info_##function.library = #lib;                                \
        array_ptr = array_push(FuncInfo, array_ptr, &func_info_##function); \
    } while(0)

// Function Assignment
void assign_functions(FuncInfo* func_info){
    // Iterate through each function in the array.
    for (size_t i = 0; i < array_length(func_info); ++i) {
        FuncInfo* func = &func_info[i];
        if(func->address){
            // Assign the address to the function pointer.
            *(func->func_ptr) = func->address;
        }
    }

    // Destroy the FuncInfo array now that we are done using it.
    array_free(func_info);
}   