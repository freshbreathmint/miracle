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
    Library* engine_lib = load_library("libengine");
    printf("engine loaded\n");
    Library* app_lib = load_library("libapplication");

    // Import the functions
    void (*import)(void*[]) = (void (*)(void*[]))get_function_pointer(app_lib->handle, "import_funcs");
    import(engine_lib->funcs);

    // we get the function pointer manually for now
    void (*runapp)() = (void (*)())get_function_pointer(app_lib->handle, "run");
    runapp();
    

    // All libs get unloaded.
    unload_all_libraries();

    // Exit
    return 0;
}