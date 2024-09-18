#include "library.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "containers/dynamic_array.h"
#include "platform/platform.h"

static Library* libraries = NULL;

Library* load_library(const char* lib_name){
    // Initialize the library array if it doesn't already exist.
    if(!libraries){
        libraries = array(Library);
    }

    // Get the handle.
    Library lib;
    lib.handle = open_library(lib_name);
    lib.name = strdup(lib_name); //FIXME: Gets freed later, probably a more elegant solution.

    // Assign API functions
    lib.import_funcs = (FuncInfo* (*)())get_function_address(lib.handle, "import_funcs");
    lib.assign_functions = (void (*)(FuncInfo*))get_function_address(lib.handle, "assign_functions");

    // Import the function info.
    FuncInfo* func_info = lib.import_funcs();

    // Iterate through each function in the array.
    for(size_t i = 0; i < array_length(func_info); ++i) {
        FuncInfo* func = &func_info[i];

        // Check if the dependant library is loaded for the specific function.
        Library* dep_lib = NULL;
        for(size_t j = 0; j < array_length(libraries); ++j) {
            if(strcmp(libraries[j].name, func->library) == 0) {
                dep_lib = &libraries[j];
                break;
            }
        }

        // Handle unloaded dependant library.
        if(!dep_lib){
            printf("Library %s not loaded. Requires dependant library: %s.\n", lib.name, func->library);
            return NULL;
        }

        // Get the function address from the dependent library.
        func->address = get_function_address(dep_lib->handle, func->name);
        if(!func->address) {
            printf(
                "Failed to get address for function '%s' from library: %s.\n",
                func->name, func->library);
            return NULL;
        }
    }

    // Now that we have the functions, assign them.
    lib.assign_functions(func_info);
    
    if(lib.handle){
        libraries = array_push(Library, libraries, &lib);
        printf("Loaded library: %s\n", lib_name);
        return &libraries[array_length(libraries) - 1];
    } else {
        printf("Failed to load library: %s\n", lib_name);
        return NULL;
    }
}

void unload_library(void* handle){
    close_library(handle);
}

void unload_all_libraries(){
    if(!libraries) return;

    // Unload each library.
    int len = array_length(libraries);
    for(int i = 0; i < len; ++i){
        free(libraries[i].name); //FIXME: See line 20.
        unload_library(libraries[i].handle);
    }

    // Free the library array itself.
    array_free(libraries);
    libraries = NULL;
}