# Overview

This documentation outlines the requirements, and current configuration of the Miracle Framework build system.

The Miracle Framework build system is designed to streamline the development process by providing an efficient and flexible system for compiling and running projects across different platforms.

The current build system utilizes Visual Studio Code tasks invoking simple bash commands for the selected platform's appropriate compilers, with future plans to transition to a more complex system. 

## Requirements

To start and build a project using the Miracle Framework, ensure you have the following:

- **Linux Environment**: Either native Linux or Windows Subsystem for Linux (WSL).
- **Visual Studio Code**:
    - Install and enable the recommended extensions for Miracle Framework.
- **Compilers**:
    - `gcc` for Linux builds.
    - `x86_64-w64-mingw32-gcc` for Windows builds.

## Details

The build system is currently implemented using several VS Code tasks, with status bar buttons to compile and run versions for both Linux and Windows.

Both the Linux and Windows build tasks use simple bash commands to invoke the respective compilers, compiling all source files in the `/src` folder and outputting the executable to the `/bin` folder.

Compilers Used:
- **Linux**: `gcc`
- **Windows**: `x86_64-w64-mingw32-gcc`

In the future, we plan to transition to a build system utilizing makefiles or CMake. This new system will accommodate the Miracle Framework as a submodule embedded within other projects.

Currently, the build system supports native Linux users or Windows Subsystem for Linux (WSL) users. To build for both Windows and Linux, it is recommended to use WSL.

### Key Challenges

1. **Hot Reloading:**
   - Hot Reloading, when implemented, should function correctly when running a Windows build natively, even if it is not as critical.
   - This should not be an issue for Linux builds.

### Planned Improvements

1. **Clean Task**
   - Add a task to clean the `/bin` folder.

## Unorganized Ideas

1. The build system should facilitate application development.
   - Setting up a new project using Miracle Framework should be straightforward and minimally cumbersome.
   - Should be as simple as adding a git submodule to the Application's project files.