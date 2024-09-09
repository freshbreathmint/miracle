#include <stdio.h>

#include "library.h"
#include "platform/platform.h"

#ifdef STATIC_LINK
#include "entry.h"
#endif //STATIC_LINK

int main()
{
#ifdef DYNAMIC_LINK
    // Load the libraries
    Library* engine_lib = load_library("libengine");
    printf("Engine library loaded.\n");
    Library* app_lib = load_library("libapplication");
    printf("Application library loaded.\n");

    // Import the engine functions to the application.
    void (*import)(void*[]) = (void (*)(void*[]))get_function_pointer(app_lib->handle, "import_funcs");
    import(engine_lib->funcs);

    // Get the entry point manually.
    void (*entry)() = (void (*)())get_function_pointer(app_lib->handle, "entry");
#endif //DYNAMIC_LINK
    
    // Run the application entry point.
    entry();
    
#ifdef DYNAMIC_LINK
    // All libs get unloaded.
    unload_all_libraries();
#endif //DYNAMIC_LINK

    // Exit
    return 0;
}