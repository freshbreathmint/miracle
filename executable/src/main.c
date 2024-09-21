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

    // Load the libraries from the config file
    if(!load_libraries_from_config("/home/mints/testapp/config.ini")){ //TODO: Local file path
        return 1;
    }
    
    // Get the application library handle
    Library* app_lib = get_loaded_library("libapplication");
    if(!app_lib){
        return 1;
    }

    // Get the applicationentry point.
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