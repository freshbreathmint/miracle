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
    Library* app_lib = load_library("libapplication");

    // Get the entry point manually.
    void (*entry)() = (void (*)())get_function_address(app_lib->handle, "entry");
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