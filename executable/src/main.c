#include <stdio.h>

#ifdef STATIC_LINK
#include "entry.h"
#endif //STATIC_LINK

int main()
{
#ifdef DYNAMIC_LINK
    #include "library.h"
    #include "platform/platform.h"
    #include "config.h"

    // Load the libraries
    load_library("libengine");
    load_library("libapplication");

    // THIS WILL REPLACE ABOVE
    if(!load_libraries_from_config("config.ini")){
        return 1;
    }
    
    // Get the application library manually (Need to make this function)
    Library* app_lib = get_loaded_library("libapplication");
    if(!app_lib){
        return 1;
    }

    // Get the entry point manually.
    void (*entry)() = (void (*)())get_function_address(app_lib->handle, "entry");
    if (!entry) {
        return 1;
    }
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