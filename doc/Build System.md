# Overview

This documentation outlines the requirements and current configuration of the Miracle Framework build system.

The Miracle Framework build system is designed to streamline the development process by providing an efficient and flexible system for compiling and running projects across various platforms. It utilizes a combination of Visual Studio Tasks and a build script, `build.sh`, which invokes CMake to generate platform-specific build files and executables using the correct toolchains.

## Requirements

To start and build a project using the Miracle Framework, ensure you have the following:

- **Linux Environment**: 
	- Either native Linux or Windows Subsystem for Linux (WSL).
- **Visual Studio Code**:
    - Install and enable the recommended extensions for Miracle Framework.
- **Compilers**:
    - `gcc` for Linux builds.
    - `x86_64-w64-mingw32-gcc` for Windows builds.
- **CMake**:
	- Version 3.30 or higher.

## Details

The build system is currently implemented on the user level using several tasks, with status bar buttons to compile and run versions for both Linux and Windows, as well as to clean the build files.

The `build.sh` script facilitates generating build directories and passing the correct arguments to CMake for platform-specific build files and toolchains. It also handles cleaning the build and bin directories.

### Build Script Overview

The `build.sh` script operates with two primary arguments: the action to be performed (`make` or `clean`) and the target platform (`native` or `windows`).

#### Usage:

- **Clean Directories:** Removes build folders and files (`/bin` & `/build`).
```sh
./build.sh clean
```

- **Build Project**: Generates build files and compiles the project for the specified platform.
```sh
./build.sh make [platform]
```

## Future Plans

The build system will be expanded to support building the application and engine libraries, as well as planned features such as hot reloading and profiling (enabling/disabling them pre-runtime during the build phase). Depending on the development of the profiling feature, it may support compiling both statically and dynamically linked versions of the executable.

For more information, please reference the [Roadmap](Roadmap.md).