#pragma once

#include <stdio.h>

// Function Info
typedef struct {
    char* library;
    char* name;
    void* address;
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
    type (*function)(__VA_ARGS__) = unbound_##function;

// Import Function Macro
#define IMPORT_FUNCTION(array_ptr, lib, function)               \
    do {                                                        \
        FuncInfo temp = {                                       \
            .library = #lib,                                    \
            .name = #function,                                  \
            .address = NULL                                     \
        };                                                      \
        array_ptr = array_push(FuncInfo, array_ptr, &temp);     \
    } while(0)

// Assign Function Macro
//#define ASSIGN_FUNCTION()
//casts the address inside of the function structure to the correct function pointer
//assigns function pointer to the declared function