#include "library.h"

#include <stddef.h>
#include <stdio.h>
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

    if(lib.handle){
        libraries = array_push(Library, libraries, &lib);
        return &libraries[array_length(libraries) - 1];
    } else {
        printf("Failed to load library: %s\n", lib_name);
        return NULL;
    }
}

void unload_libraries(){
    if(!libraries) return;

    int len = array_length(libraries);
    for(int i = 0; i < len; ++i){
        close_library(libraries[i].handle);
    }
    array_free(libraries);
    libraries = NULL;
}