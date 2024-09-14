#pragma once

/* [STATIC LINKING] */
#ifdef STATIC_LINK
//#include ""   // type function(args)
#endif //STATIC_LINK

/* [DYNAMIC LINKING] */
#ifdef DYNAMIC_LINK
#include "libapi_dynamic.h"
#include "containers/dynamic_array.h"

// Function Declarations
//DECLARE_FUNCTION(TYPE, FUNCTION, ARGS)

// Function Import
FuncInfo* import_funcs(){
    FuncInfo* info = array(FuncInfo);
 
    //IMPORT_FUNCTION(info, LIBRARY, FUNCTION)

    return info;
}
#endif //DYNAMIC_LINK