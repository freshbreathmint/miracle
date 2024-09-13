#pragma once

#include <stdio.h>

/* [MACROS] */
// Unbound Function
void unbound_function(const char *function_name) {
    printf("Tried to call an unbound function: %s\n", function_name);
}

// Function Declaration Macro
#define DECLARE_FUNCTION(return_type, function, ...)             \
    return_type unbound_##function(__VA_ARGS__) {               \
        unbound_function(#function);                            \
        return (return_type)0;                                  \
    }                                                           \
    return_type (*function)(__VA_ARGS__) = unbound_##function;

// Import Function Macro
//#define IMPORT_FUNCTION()
//adds new function structure to the array, fills out information

// Assign Function Macro
//#define ASSIGN_FUNCTION()
//casts the address inside of the function structure to the correct function pointer
//assigns function pointer to the declared function

/* [STATIC LINKING] */
#ifdef STATIC_LINK
//#include ""   // type function(args)
//#include ""   // type function(args)
//#include ""   // type function(args)
#endif //STATIC_LINK

/* [DYNAMIC LINKING] */
#ifdef DYNAMIC_LINK
// Function Declarations
//DECLARE_FUNCTION(TYPE, FUNCTION, ARGS)
//DECLARE_FUNCTION(TYPE, FUNCTION, ARGS)
//DECLARE_FUNCTION(TYPE, FUNCTION, ARGS)

// Function Import
void import_funcs(){
    // create a new array of function structures

    //IMPORT_FUNCTION()
    //IMPORT_FUNCTION()
    //IMPORT_FUNCTION()

    //returns a pointer to the function array
}

// Function Assignment
void assign_functions(){
    // we automatically go through the function list and assign each one with a non-null address 
    // to the relevant declared function pointer. we can probably use a macro for this maybe.
}
#endif //DYNAMIC_LINK