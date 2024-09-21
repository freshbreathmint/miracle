#pragma once

#include <stdbool.h>

typedef struct LibraryEntry {
    char *name;             // Name of the library
    bool is_dynamic;        // True if type == "dynamic"
    char **dependencies;    // Dynamic array of dependency names
} LibraryEntry;

bool load_libraries_from_config(const char* config_file);