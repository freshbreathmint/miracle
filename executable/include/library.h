#pragma once

// Function Info
typedef struct {
    char* library;
    char* name;
    void* address;
    void** func_ptr;
} FuncInfo;

// Library Structure
typedef struct {
    char* name;
    void* handle;
    FuncInfo* (*import_funcs)();            //import_funcs()
    void (*assign_functions)(FuncInfo*);    //assign_functions(FuncInfo*)
} Library;

Library* load_library(const char* lib_name);
Library* get_loaded_library(const char* lib_name);
void unload_all_libraries();