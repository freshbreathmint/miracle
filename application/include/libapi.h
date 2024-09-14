#pragma once

/* [STATIC LINKING] */
#ifdef STATIC_LINK
//#include ""   // type function(args)
//#include ""   // type function(args)
//#include ""   // type function(args)
#endif //STATIC_LINK

/* [DYNAMIC LINKING] */
//#ifdef DYNAMIC_LINK
#include "libapi_dynamic.h"
#include "containers/dynamic_array.h"

// Function Declarations
DECLARE_FUNCTION(void, funcA)
//DECLARE_FUNCTION(TYPE, FUNCTION, ARGS)
//DECLARE_FUNCTION(TYPE, FUNCTION, ARGS)

// Function Import
FuncInfo* import_funcs(){
    FuncInfo* func_info = array(FuncInfo);
 
    IMPORT_FUNCTION(func_info, engine, funcA);
    //IMPORT_FUNCTION()
    //IMPORT_FUNCTION()

    return func_info;
}

// Function Assignment
void assign_functions(){
    // we automatically go through the provided function list and assign each one with a non-null 
    // address to the relevant declared function pointer. we can probably use a macro for this maybe.

    // destroy the function list (burn after reading!)
}
//#endif //DYNAMIC_LINK