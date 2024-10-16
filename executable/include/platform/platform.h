#pragma once

/* PLATFORM DETECTION */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define PLATFORM_WINDOWS 1
    #if defined(_WIN64)
        #define PLATFORM_WINDOWS_64 1
    #else
        #define PLATFORM_WINDOWS_32 1
    #endif
#elif defined(__linux__) || defined(__linux)
    #define PLATFORM_LINUX 1
#else
    #error "MIRACLE: Unknown/Unsupported Platform"
#endif

/* LIBRARY LOADING */
void* open_library(const char* lib_name);
void* get_function_address(void* handle, const char* func_name);
void close_library(void* handle);

/* MISC */
char* get_executable_path();