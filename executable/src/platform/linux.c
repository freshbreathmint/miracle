#include "platform/platform.h"

#if PLATFORM_LINUX

#include <dlfcn.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void* get_function_address(void* handle, const char* func_name) {
    // Get the function address
    void* function_addr = dlsym(handle, func_name);
   
    // Check for errors
    char* error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error finding symbol: %s\n", error);
        return NULL;
    }

    return function_addr;
}

void close_library(void* handle) {
    if (handle) {
        dlclose(handle);
    }
}

char* get_executable_path() {
    ssize_t len = 0;
    size_t buffer_size = PATH_MAX;
    char* full_path = NULL;

    // Loop to handle buffer size
    while (1) {
        full_path = (char*)malloc(buffer_size);
        if (!full_path) {
            // Memory allocation failed
            return NULL;
        }

        len = readlink("/proc/self/exe", full_path, buffer_size - 1);
        if (len == -1) {
            // Failed to read the symbolic link
            free(full_path);
            return NULL;
        }

        if ((size_t)len < buffer_size - 1) {
            // Successfully retrieved the path
            full_path[len] = '\0'; // Null-terminate the string
            break;
        }

        // Buffer was too small, increase size and try again
        free(full_path);
        buffer_size *= 2;

        // Prevent excessively large buffer
        if (buffer_size > 65536) { // 64KB limit
            return NULL;
        }
    }

    // Find the last forward slash '/'
    char* last_slash = strrchr(full_path, '/');
    if (!last_slash) {
        // Invalid path format
        free(full_path);
        return NULL;
    }

    // Calculate directory path length
    size_t dir_length = last_slash - full_path + 1; // Include the slash

    // Allocate memory for directory path
    char* dir_path = (char*)malloc(dir_length + 1); // +1 for null terminator
    if (!dir_path) {
        free(full_path);
        return NULL;
    }

    strncpy(dir_path, full_path, dir_length);
    dir_path[dir_length] = '\0'; // Null-terminate

    free(full_path);
    return dir_path;
}


#endif //PLATFORM_LINUX