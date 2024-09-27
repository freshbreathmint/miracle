#include "platform/platform.h"

#if PLATFORM_WINDOWS

#include <stdio.h>
#include <windows.h>

void* open_library(const char* lib_name) {
    // Add .dll to the end of the library name
    char lib_name_dll[256];
    strcpy(lib_name_dll, lib_name);
    strcat(lib_name_dll, ".dll");

    // Load the library
    HMODULE handle = LoadLibrary(lib_name_dll);
    if (!handle) {
        fprintf(stderr, "Error loading library: %lu\n", GetLastError());
        return NULL;
    }

    return handle;
}

void* get_function_address(void* handle, const char* func_name) {
    // Get the function address
    void* function_addr = GetProcAddress((HMODULE)handle, func_name);

    // Check for errors
    if (!function_addr) {
        fprintf(stderr, "Error finding symbol: %lu\n", GetLastError());
        return NULL;
    }

    return function_addr;
}

void close_library(void* handle) {
    if (handle) {
        FreeLibrary((HMODULE)handle);
    }
}

char* get_executable_path() {
    DWORD buffer_size = MAX_PATH;
    DWORD size = 0;
    char* full_path = NULL;

    // Loop to handle buffer size
    while (1) {
        full_path = (char*)malloc(buffer_size);
        if (!full_path) {
            // Memory allocation failed
            return NULL;
        }

        size = GetModuleFileNameA(NULL, full_path, buffer_size);
        if (size == 0) {
            // Failed to get module file name
            free(full_path);
            return NULL;
        }

        if (size < buffer_size) {
            // Successfully retrieved the path
            break;
        }

        // Buffer was too small, increase size and try again
        free(full_path);
        buffer_size *= 2;

        // Prevent infinite loop
        if (buffer_size > 32768) { // 32KB limit
            return NULL;
        }
    }

    // Find the last backslash '\\'
    char* last_backslash = strrchr(full_path, '\\');
    if (!last_backslash) {
        // Invalid path format
        free(full_path);
        return NULL;
    }

    // Calculate directory path length
    size_t dir_length = last_backslash - full_path + 1; // Include the backslash

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

#endif //PLATFORM_WINDOWS