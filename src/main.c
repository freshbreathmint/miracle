#include <stdio.h>
#include <dlfcn.h>

int main()
{
    // Load Library
    void *handle = dlopen("./bin/linux/debug/libapplication.so", RTLD_LAZY); 
    //TODO: this path is for some reason relative to where the application has been LAUNCHED from
    //      meaning that it's useless if you're not launching from the VSC run task. Alternatively
    //      if I were to remove the bin/linux/debug/ portion of it, it would be runnable from the
    //      actual directory without a problem. Not sure how to fix this at the moment
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