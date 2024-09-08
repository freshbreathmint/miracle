#pragma once

typedef struct {
    void* handle;
    void** funcs;
} Library;

Library* load_library(const char* lib_name);
void unload_all_libraries();