# Overview

This document serves as a guide for developing applications using the Miracle Framework.

## Details

### Setting Up Application

To set up a default application using the Miracle Framework, follow these steps:

1. **Download the Extension**: Install the Miracle Framework extension for Visual Studio Code.
2. **Initialize a Git Repository**: Initialize a Git repository in the project folder.
3. **Set Up the Workspace**: Click "Setup Workspace" to automatically create a default application in your project folder and clone the framework as a submodule.
4. **Name the Application**: Provide a name for the application when prompted.

## Breakdown

### entry()

The `entry.c` file contains the entry point for your application. This function is executed automatically once the framework has finished loading.

Here's the default implementation:
```c
#include "entry.h"
#include "libapi.h"

#include <stdio.h>

void entry(){
    printf("Application says hello!\n");
}
```

This `entry()` function runs at the start of your application and outputs a message to the console.

### Library API

The `libapi.h` file is a header where users can specify the functions to be imported by the framework when the application is dynamically loaded.

By default, the file looks like this:
```c
#pragma once

/* [STATIC LINKING] */
#ifdef STATIC_LINK
//#include ""   // type function(args)
#endif //STATIC_LINK


/* [DYNAMIC LINKING] */
#ifdef DYNAMIC_LINK
#include "core/function.h"

// Function Declarations
//DECLARE_FUNCTION(TYPE, FUNCTION, ARGS)

// Function Import
FuncInfo* import_funcs(){
    FuncInfo* info = array(FuncInfo);
    
    //IMPORT_FUNCTION(info, LIBRARY, FUNCTION)
    
    return info;
}
#endif //DYNAMIC_LINK
```

### Using the Library API

When importing functions from dynamic libraries, the user must define them in the `libapi.h` file. This ensures they are loaded correctly by the framework during runtime.

Let’s break this process down into three sections. We will demonstrate how to import the function `add()` from the library `libexample`.

#### 1. Static Linking

If you are statically linking your binary, include the required headers within the `STATIC_LINK` block.
```c
/* [STATIC LINKING] */
#ifdef STATIC_LINK
#include "example.h" // int add(int num1, int num2)
#endif //STATIC_LINK
```
In this case, the function `add()` will be baked into the binary via `libexample` during compilation. assuming that `add()` exists in `example.h`.

#### 2. Function Declaration

Next, declare the function using the provided macros:
```c
// Function Declarations
DECLARE_FUNCTION(void, add, int num1, int num2);
```
This macro generates a function declaration for `void add(int num1, int num2)`, which will be available in the application.

#### 3. Function Import

The third section is a function used by the framework that generates a list of functions to import from other libraries using a macro:
```c
// Function Import
FuncInfo* import_funcs(){
    FuncInfo* info = array(FuncInfo);
    
    IMPORT_FUNCTION(info, example, add); 
    
    return info;
}
```
Here, the framework will attempt to locate the function `add` in the library `libexample` when the application is loaded.