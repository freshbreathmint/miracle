#include <stdio.h>
#include <dlfcn.h>

//path stuff
#include <unistd.h>
#include <libgen.h>

int main()
{
    // Get path of the executable
    char exe_path[4096];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    exe_path[len] = '\0'; // Null-terminate the path
    printf("Executable Path: %s\n", exe_path);

    // Get the directory
    char *dir = dirname(exe_path);

    // Construct the path to the shared library
    char lib_path[4096];
    snprintf(lib_path, sizeof(lib_path), "%s/libapplication.so", exe_path);
    printf("Library Path: %s\n", lib_path);

    // Load Library
    void *handle = dlopen(lib_path, RTLD_LAZY); 
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Function Pointer
    int (*function_ptr) ();
    function_ptr = dlsym(handle, "measure_flops");
    
    // Check Errors
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Run Loop
    int loops = 0;
    while(loops < 5){
        int flops = function_ptr();
        printf("FLOPS: %i\n", flops);
        loops++;
    }

    // Close Library
    dlclose(handle);

    // Exit
    return 0;
}