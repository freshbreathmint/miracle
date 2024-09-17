# Overview

The **Miracle Framework** is a versatile software framework designed to facilitate the development of modular applications across multiple platforms, specifically Windows and Linux. It supports both **dynamic** and **static linking**, allowing developers to choose the most suitable method for their project needs. This API Reference provides comprehensive information on the framework's functions, macros, and processes, along with a practical example demonstrating how to import functions from other libraries.

## Understanding the Dynamic Linker

The **Dynamic Linker** within the Miracle Framework manages the loading of shared libraries at runtime, resolving dependencies, and binding functions. This allows applications to be modular, enabling functionalities to be added or updated without recompiling the entire application.

**Key Concepts:**

- **Dynamic Linking:** Loading libraries during runtime rather than at compile time.
- **Function Binding:** Associating function names with their corresponding addresses in the loaded libraries.
- **Dependency Management:** Ensuring that all required libraries are loaded in the correct order before their dependent libraries.

**Important Note:** The Miracle Framework **does not** automatically load dependent libraries. It is the developer's responsibility to load libraries in the correct order to satisfy dependencies. If a required library is not loaded before a dependent library, the framework will fail to load the dependent library and provide an error message.

## Creating a New Library (`libmath`)

In this example, we will create a new library named `libmath` that provides basic mathematical functions. This library will be dynamically loaded by the application to perform arithmetic operations.

### 1. Define the Library Interface

First, define the interface for `libmath` by creating a header file that declares the functions to be provided.

#### `math.h`
```c
#pragma once

/**
 * @brief Adds two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return int Sum of a and b.
 */
int add(int a, int b);

/**
 * @brief Multiplies two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return int Product of a and b.
 */
int multiply(int a, int b);

/**
 * @brief Subtracts the second integer from the first.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return int Difference of a and b.
 */
int subtract(int a, int b);

/**
 * @brief Divides the first integer by the second.
 *        Returns 0 if division by zero is attempted.
 *
 * @param a Dividend.
 * @param b Divisor.
 * @return int Result of division or 0 if b is zero.
 */
int divide(int a, int b);
```

### 2. Implement the Library

Implement the declared functions in the source file.

#### `math.c`
```c
#include "math.h"

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int subtract(int a, int b) {
    return a - b;
}

int divide(int a, int b) {
    if (b == 0) {
        // Handle division by zero gracefully
        return 0;
    }
    return a / b;
}
```

_Note:_ In the future, support will be added to the build script to specify and compile such libraries automatically, streamlining the integration process.

## Integrating `libmath` into the Application

To utilize the functions provided by `libmath` within your application, follow these steps:

### 1. Declare and Import Functions

Modify the application library to declare and import the functions provided by `libmath`.

#### `libapi.h`
```c
#pragma once

/* [STATIC LINKING] */
#ifdef STATIC_LINK
#include "math.h"
/**
 * int add(int, int)
 * int multiply(int, int)
 * int subtract(int, int)
 * int divide(int, int)
 */
#endif //STATIC_LINK

/* [DYNAMIC LINKING] */
#ifdef DYNAMIC_LINK
#include "libapi_dynamic.h"

// Function Declarations
DECLARE_FUNCTION(int, add, int, int);
DECLARE_FUNCTION(int, multiply, int, int);
DECLARE_FUNCTION(int, subtract, int, int);
DECLARE_FUNCTION(int, divide, int, int);

// Function Import
FuncInfo* import_funcs() {
    FuncInfo* info = array(FuncInfo);

    IMPORT_FUNCTION(info, libmath, add);
    IMPORT_FUNCTION(info, libmath, multiply);
    IMPORT_FUNCTION(info, libmath, subtract);
    IMPORT_FUNCTION(info, libmath, divide);

    return info;
}
#endif // DYNAMIC_LINK
```

**Explanation:**

- **Static Linking:**
  - Add the relevant include for the library when it is statically linked, automatically giving statically linked code the same access through libapi.h 
- **DECLARE_FUNCTION Macros:**
  - Each `DECLARE_FUNCTION` macro declares a function pointer for the corresponding mathematical function.
  - If the function is not bound, calling it will invoke an `unbound_function`, which logs an error.
- **IMPORT_FUNCTION Macros:**
  - Each `IMPORT_FUNCTION` macro specifies the library (`libmath`) and the function to import.
  - These macros add entries to the `FuncInfo` array, which the framework uses to resolve and bind the functions.

### 2. Update the Entry Point

Utilize the imported functions within the application's entry point.

#### `entry.c`
```c
#include "entry.h"
#include "libapi.h"
#include <stdio.h>

void entry() {
    printf("Application Entry Point\n");

    int a = 20;
    int b = 4;

    int sum = add(a, b);
    int product = multiply(a, b);
    int difference = subtract(a, b);
    int quotient = divide(a, b);

    printf("%d + %d = %d\n", a, b, sum);
    printf("%d * %d = %d\n", a, b, product);
    printf("%d - %d = %d\n", a, b, difference);
    printf("%d / %d = %d\n", a, b, quotient);
}
```
**Explanation:**

- **Function Usage:**
  - The `entry` function calls the imported mathematical functions and prints their results.
  - This demonstrates how functions from `libmath` are seamlessly integrated and used within the application.

## Configuring the Main Application

Update the main application to load both `libmath` and `libapplication`, and then execute the application's entry point.

### 1. Update `main.c`

Ensure that `main.c` is set up to load the necessary libraries and invoke the entry point.

#### `main.c`
```c
#include <stdio.h>
#include "library.h"
#include "platform/platform.h"

#ifdef DYNAMIC_LINK
#include "entry.h"
#endif // DYNAMIC_LINK

int main() {
#ifdef DYNAMIC_LINK
    // Load the math library first to satisfy dependencies
    Library* math_lib = load_library("libmath");

    // Load the application library
    Library* app_lib = load_library("libapplication");

    // Get the entry point from the application library
    void (*entry)() = (void (*)())get_function_address(app_lib->handle, "entry");
#endif // DYNAMIC_LINK

    // Run the application entry point
    entry();

#ifdef DYNAMIC_LINK
    // Unload all libraries
    unload_all_libraries();
#endif // DYNAMIC_LINK

    return 0;
}
```

**Explanation:**

- **Loading Libraries:**
  - `libmath` is explicitly loaded before `libapplication` to ensure its functions are available when `libapplication` is loaded.
  - The framework **does not** automatically load dependent libraries. Libraries must be loaded in the correct order to satisfy dependencies.
- **Retrieving Entry Point:**
  - The `entry` function from `libapplication` is retrieved using `get_function_address` and then invoked.

_Note:_ Future updates will include support for specifying libraries to be loaded at runtime utilizing an initialization file, further simplifying the integration process and reducing manual configuration.



