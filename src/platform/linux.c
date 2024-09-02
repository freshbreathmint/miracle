#include "platform/platform.h"

#if PLATFORM_LINUX

#include <dlfcn.h>
#include <libgen.h>
#include <stdio.h>
#include <unistd.h>

void* open_library(const char* lib_name) {
    // Get path of the executable
    char exe_path[4096];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len == -1) {
        perror("readlink");
        
    }
    exe_path[len] = '\0'; // Null-terminate the path

    // Get the directory of the executable
    char* dir = dirname(exe_path);

    // Construct the path to the shared library
    char lib_path[4096];
    snprintf(lib_path, sizeof(lib_path), "%s/%s.so", dir, lib_name);

    // Load the library
    void* handle = dlopen(lib_path, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return NULL;
    }

    return handle;
}

void (*get_function_pointer(void* handle, const char* func_name))() {
    // Get the function pointer
    void (*function_ptr)() = dlsym(handle, func_name);
   
    // Check for errors
    char* error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error finding symbol: %s\n", error);
        return NULL;
    }

    return function_ptr;
}

void close_library(void* handle) {
    if (handle) {
        dlclose(handle);
    }
}

#endif //PLATFORM_LINUX