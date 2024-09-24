#include "config.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"

#include "containers/dynamic_array.h"
#include "ini.h"

typedef struct {
    LibraryEntry** libraries;   // Dynamic array of LibraryEntry pointers
    char** app_dependencies;    // Dynamic array of application dependency names
} ConfigContext;

// Function to find LibraryEntry by name
static LibraryEntry* find_library_entry(LibraryEntry** libraries, const char* name) {
    size_t len = array_length(libraries);
    for (size_t i = 0; i < len; i++) {
        if (strcmp(libraries[i]->name, name) == 0) {
            return libraries[i];
        }
    }
    return NULL;
}

// Check if a library name is already in the list
static bool is_in_list(char** list, const char* name) {
    size_t len = array_length(list);
    for (size_t i = 0; i < len; i++) {
        if (strcmp(list[i], name) == 0) {
            return true;
        }
    }
    return false;
}

// Recursive function to process library dependencies
static void process_library(const char* lib_name, ConfigContext* context, char*** load_list) {
    // Check if lib_name is already in load_list
    if (is_in_list(*load_list, lib_name)) {
        return;
    }

    // Find the LibraryEntry for lib_name
    LibraryEntry* lib = find_library_entry(context->libraries, lib_name);
    if (!lib) {
        printf("Error: Library '%s' not found.\n", lib_name);
        return;
    }

    // If library is not dynamic, ignore
    if (!lib->is_dynamic) {
        return;
    }

    // Process dependencies
    if (lib->dependencies) {
        size_t dep_len = array_length(lib->dependencies);
        for (size_t i = 0; i < dep_len; i++) {
            const char* dep_name = lib->dependencies[i];
            process_library(dep_name, context, load_list);
        }
    }

    // After processing dependencies, add lib_name to load_list
    char* fixed_name = malloc(strlen(lib_name) + strlen("lib") + 1);
    strcpy(fixed_name, "lib");
    strcat(fixed_name, lib_name);
    *load_list = array_push(char*, *load_list, &fixed_name);
}

// Handler function for ini_parse
static int handler(void* user, const char* section, const char* name, const char* value) {
    ConfigContext* context = (ConfigContext*)user;

    // Initialize libraries array if it's NULL
    if (context->libraries == NULL) {
        context->libraries = array(LibraryEntry*);
    }

    if (strcmp(section, "application") == 0) {
        if (strcmp(name, "dependencies") == 0) {
            // Parse dependencies
            if (context->app_dependencies != NULL) {
                // Clear existing dependencies if any
                size_t dep_len = array_length(context->app_dependencies);
                for (size_t i = 0; i < dep_len; i++) {
                    free(context->app_dependencies[i]);
                }
                array_free(context->app_dependencies);
            }
            context->app_dependencies = array(char*);

            // Parse the dependencies, which are comma-separated
            char* deps = strdup(value);
            if (!deps) {
                fprintf(stderr, "Error: Memory allocation failed while parsing dependencies.\n");
                return 0; // Stop parsing
            }
            char* token = strtok(deps, ",");
            while (token != NULL) {
                // Trim leading whitespace
                while (isspace((unsigned char)*token)) token++;
                // Trim trailing whitespace
                char* end = token + strlen(token) - 1;
                while (end > token && isspace((unsigned char)*end)) end--;
                end[1] = '\0';

                char* dep_name = strdup(token);
                if (!dep_name) {
                    fprintf(stderr, "Error: Memory allocation failed for dependency '%s'.\n", token);
                    free(deps);
                    return 0; // Stop parsing
                }
                context->app_dependencies = array_push(char*, context->app_dependencies, &dep_name);
                token = strtok(NULL, ",");
            }
            free(deps);
        }
        // Handle other keys in [application] if needed
    } else if (strncmp(section, "library.", 8) == 0) {
        const char* library_name = section + 8; // Skip "library."

        // Find or create the LibraryEntry for this library
        LibraryEntry* library = find_library_entry(context->libraries, library_name);
        if (!library) {
            // Create new LibraryEntry
            library = malloc(sizeof(LibraryEntry));
            if (!library) {
                fprintf(stderr, "Error: Memory allocation failed for library '%s'.\n", library_name);
                return 0; // Stop parsing
            }
            library->name = strdup(library_name);
            if (!library->name) {
                fprintf(stderr, "Error: Memory allocation failed for library name '%s'.\n", library_name);
                free(library);
                return 0; // Stop parsing
            }
            library->is_dynamic = false;   // Default to false
            library->dependencies = NULL;  // Initialize dependencies dynamic array

            // Push the new library into the libraries array
            context->libraries = array_push(LibraryEntry*, context->libraries, &library);
        }

        // Process the name/value pairs
        if (strcmp(name, "type") == 0) {
            if (strcmp(value, "dynamic") == 0) {
                library->is_dynamic = true;
            } else if (strcmp(value, "static") == 0) {
                library->is_dynamic = false;
            } else {
                printf("Unknown type '%s' for library '%s'\n", value, library_name);
            }
        } else if (strcmp(name, "dependencies") == 0) {
            // Clear existing dependencies if any
            if (library->dependencies) {
                size_t dep_len = array_length(library->dependencies);
                for (size_t i = 0; i < dep_len; i++) {
                    free(library->dependencies[i]);
                }
                array_free(library->dependencies);
            }
            library->dependencies = array(char*);

            // Parse the dependencies, which are comma-separated
            if (strlen(value) > 0) { // Only parse if dependencies are listed
                char* deps = strdup(value);
                if (!deps) {
                    fprintf(stderr, "Error: Memory allocation failed while parsing dependencies for library '%s'.\n", library_name);
                    return 0; // Stop parsing
                }
                char* token = strtok(deps, ",");
                while (token != NULL) {
                    // Trim leading whitespace
                    while (isspace((unsigned char)*token)) token++;
                    // Trim trailing whitespace
                    char* end = token + strlen(token) - 1;
                    while (end > token && isspace((unsigned char)*end)) end--;
                    end[1] = '\0';

                    char* dep_name = strdup(token);
                    if (!dep_name) {
                        fprintf(stderr, "Error: Memory allocation failed for dependency '%s' in library '%s'.\n", token, library_name);
                        free(deps);
                        return 0; // Stop parsing
                    }
                    library->dependencies = array_push(char*, library->dependencies, &dep_name);
                    token = strtok(NULL, ",");
                }
                free(deps);
            }
        } else if (strcmp(name, "path") == 0) {
            // Acknowledge the 'path' key but do not store it
        } else {
            // Handle other keys if necessary
            printf("Unknown key '%s' in section '%s'\n", name, section);
        }
    }

    return 1; // Return 1 to continue parsing
}

bool load_libraries_from_config(const char* config_file) {
    bool success = true;
    ConfigContext context;
    context.libraries = NULL;        // Initialize the dynamic array
    context.app_dependencies = NULL; // Initialize application dependencies

    // Parse config file
    if (ini_parse(config_file, handler, &context) < 0) {
        printf("Error parsing config file.\n");
        success = false;
    } else {
        // Process application dependencies
        char** load_list = array(char*);
        if (context.app_dependencies) {
            size_t app_dep_len = array_length(context.app_dependencies);
            for (size_t i = 0; i < app_dep_len; i++) {
                const char* dep_name = context.app_dependencies[i];
                process_library(dep_name, &context, &load_list);
            }
        } else {
            printf("No application dependencies found.\n");
        }

        // Load the libraries
        size_t load_list_len = array_length(load_list);
        for (size_t i = 0; i < load_list_len; i++) {
            load_library(load_list[i]);
        }

        // Clean up load_list
        for (size_t i = 0; i < load_list_len; i++) {
            free(load_list[i]);
        }
        array_free(load_list);

        // Load the application
        load_library("libapplication");
    }

    // Clean up application dependencies
    if (context.app_dependencies) {
        size_t dep_len = array_length(context.app_dependencies);
        for (size_t i = 0; i < dep_len; i++) {
            free(context.app_dependencies[i]);
        }
        array_free(context.app_dependencies);
    }

    // Clean up libraries
    if (context.libraries) {
        size_t lib_len = array_length(context.libraries);
        for (size_t i = 0; i < lib_len; i++) {
            LibraryEntry* lib = context.libraries[i];
            free(lib->name);

            if (lib->dependencies) {
                size_t dep_len = array_length(lib->dependencies);
                for (size_t j = 0; j < dep_len; j++) {
                    free(lib->dependencies[j]);
                }
                array_free(lib->dependencies);
            }
            free(lib);
        }
        array_free(context.libraries);
    }

    return success;
}