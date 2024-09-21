#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"
#include "containers/dynamic_array.h"

typedef struct {
    LibraryEntry** libraries;           // Dynamic array of LibraryEntry pointers
    char** application_dependencies;    // Dynamic array of application dependencies
    char* current_section;              // Section being parsed
    LibraryEntry* current_library;      // Library entry being parsed
} ParsingContext;

static int handler(void* user, const char* section, const char* name, const char* value){
    ParsingContext* context = (ParsingContext*)user;

    // Handle new section
    if(context->current_section == NULL || strcmp(section, context->current_section) != 0){
        if(context->current_section){
            free(context->current_section);
        }
        context->current_section = strdup(section);
        context->current_library = NULL;
    }

    // Handle [application] section
    if(strcmp(section, "application") == 0){
        if(strcmp(name, "dependencies") == 0){
            //Parse dependencies
            const char* p = value;
            while(*p){
                while(*p == ' ') p++;
                const char* start = p;
                while(*p && *p != ',' && *p != ' ') p++;
                size_t len = p - start;
                if(len > 0){
                    char* dep_name = malloc(len + 1);
                    strncpy(dep_name, start, len);
                    dep_name[len] = '\0';
                    context->application_dependencies = array_push(
                        char*, context->application_dependencies, &dep_name);
                }
                while(*p == ',' || *p == ' ') p++;
            }
        }
        return 1;
    }

    // Handle [library] sections
    if (strncmp(section, "library.", 8) == 0) {
        // Extract library name
        const char* lib_name = section + 8;

        // If current_library is NULL or not the same as lib_name, find or create the LibraryEntry
        if(!context->current_library || strcmp(context->current_library->name, lib_name) != 0){
            // Search for existing LibraryEntry
            LibraryEntry* lib_entry = NULL;
            for(size_t i = 0; i < array_length(context->libraries); i++){
                if(strcmp(context->libraries[i]->name, lib_name) == 0){
                    lib_entry = context->libraries[i];
                    break;
                }
            }
            // If not found, create a new LibraryEntry
            if(!lib_entry){
                lib_entry = malloc(sizeof(LibraryEntry));
                lib_entry->name = strdup(lib_name);
                lib_entry->type = NULL;
                lib_entry->dependencies = NULL;
                context->libraries = array_push(LibraryEntry*, context->libraries, &lib_entry);
            }
            context->current_library = lib_entry;
        }

        // Handle key-value pairs
        if(strcmp(name, "type") == 0) {
            if(context->current_library->type) {
                free(context->current_library->type);
            }
            context->current_library->type = strdup(value);
        } else if (strcmp(name, "dependencies") == 0) {
            // Parse dependencies
            const char* p = value;
            while(*p){
                while (*p == ' ') p++;
                const char* start = p;
                while(*p && *p != ',' && *p != ' ') p++;
                size_t len = p - start;
                if(len > 0){
                    char* dep_name = malloc(len + 1);
                    strncpy(dep_name, start, len);
                    dep_name[len] = '\0';
                    context->current_library->dependencies = array_push(
                        char*, context->current_library->dependencies, &dep_name);
                }
                while(*p == ',' || *p == ' ') p++;
            }
        }
        return 1;
    }

    // Ignore other sections
    return 1;
}

bool load_libraries_from_config(const char* config_file){
    // Initialize parsing context.
    ParsingContext context = {0};
    context.libraries = array(LibraryEntry*);
    context.application_dependencies = array(char*);

    // Parse config file
    if(ini_parse(config_file, handler, &context) < 0){
        printf("Error parsing config file.\n");
        return false;
    }

    // Success
    return true;
}