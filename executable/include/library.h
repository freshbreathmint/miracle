#pragma once

typedef struct {
    void* handle;
} Library;

Library* load_library(const char* lib_name);
void unload_libraries();