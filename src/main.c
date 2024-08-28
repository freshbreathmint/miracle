#include "platform/platform.h"
#include <stdio.h>

int main()
{
    // Open the application library
    void* handle = open_library("libapplication");
    if(!handle) {
        return 1;
    }

    // Get the function pointer
    int (*function_ptr)() = get_function_pointer(handle, "measure_flops");
    if (!function_ptr) {
        close_library(handle);
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
    close_library(handle);

    // Exit
    return 0;
}