#pragma once

#include <stdbool.h>

typedef struct LibraryEntry {
    char *name;             // Name of the library
    char *type;             // "dynamic" or "static"
    char **dependencies;    // Dynamic array of dependency names
} LibraryEntry;

bool load_libraries_from_config(const char* config_file);