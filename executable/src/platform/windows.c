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

void (*get_function_pointer(void* handle, const char* func_name))() {
    // Get the function pointer
    void (*function_ptr)() = (void (*)())GetProcAddress((HMODULE)handle, func_name);

    // Check for errors
    if (!function_ptr) {
        fprintf(stderr, "Error finding symbol: %lu\n", GetLastError());
        return NULL;
    }

    return function_ptr;
}

void close_library(void* handle) {
    if (handle) {
        FreeLibrary((HMODULE)handle);
    }
}

#endif //PLATFORM_WINDOWS