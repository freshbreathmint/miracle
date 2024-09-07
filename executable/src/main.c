#include <stdbool.h>
#include <stdio.h>
#include "library.h"
#include "platform/platform.h"

bool running = false;

int main()
{
    running = true;

    // Main Loop
    int cycle = 0;
    while(running){
        cycle++;
        printf("Cycle: %i\n", cycle);
        if(cycle == 100000){
            running = false;
        }
    }

    // We can load the library dynamically into an array of libraries
    Library* app_lib = load_library("libapplication");
    Library* engine_lib = load_library("libengine");

    // we get the function pointer manually for now
    void (*runapp)() = (void (*)())get_function_pointer(app_lib->handle, "run");
    void (*runengine)() = (void (*)())get_function_pointer(engine_lib->handle, "run");
    runapp();
    runengine();

    // All libs get unloaded.
    unload_libraries();

    // Exit
    return 0;
}