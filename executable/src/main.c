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
        if(cycle == 1){
            running = false;
        }
    }

    // We can load the library dynamically into an array of libraries
    Library* app_lib = load_library("libapplication");
    Library* engine_lib = load_library("libengine");

    void (*funcA)() = (void (*)())engine_lib->funcs[0];
    funcA();

    void (*funcB)() = (void (*)())engine_lib->funcs[1];
    funcB();

    // we get the function pointer manually for now
    // void (*runengine)() = (void (*)())get_function_pointer(engine_lib->handle, "run");
    // runapp();
    // runengine();

    // All libs get unloaded.
    unload_all_libraries();

    // Exit
    return 0;
}