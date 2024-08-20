# Overview

This documentation provides a detailed outline of the requirements and current configuration of the Miracle Framework build system.

The Miracle Framework build system is designed to optimize the development process by offering an efficient and streamlined process for compiling and running projects across various platforms. It integrates Visual Studio Code tasks with a custom build script, `build.sh`, which leverages CMake to generate platform-specific build files and executables using the appropriate toolchains.

## Requirements

To begin building a project with the Miracle Framework, ensure you have the following:

- **Linux Environment**: 
	- Either native Linux or Windows Subsystem for Linux (WSL).
- **Visual Studio Code**:
    - Install and enable the recommended extensions for the Miracle Framework.
- **Compilers**:
    - `gcc` for Linux builds.
    - `x86_64-w64-mingw32-gcc` for cross-compiled Windows builds.
- **CMake**:
	- Version 3.30 or higher.

## Details

The build system is currently implemented at the user level through several tasks accessible via the Visual Studio Code status bar. When you select "Linux/WSL Tasks," you'll have options to clean, run, build, cross-compile, or generate release builds.

The `build.sh` script is central to this process. It handles the creation of build directories and passes the appropriate arguments to CMake to generate platform-specific build files and configure toolchains. Additionally, it manages the cleanup of the build and binary directories. The `run.sh` script is used to launch the compiled executable in a new bash window.

### Build Script Overview

The `build.sh` script is designed to streamline the build process with a focus on platform-specific configurations. It supports two primary actions: cleaning the build directories and building the project for either a native or Windows environment. Additionally, it offers an option to perform debug builds.

#### Usage:

- **Clean Directories:** Removes the existing build and binary directories (`/build` & `/bin`).
```sh
./build.sh clean
```

- **Build Project**: Generates the necessary build files and compiles the project for the specified platform (`linux` or `windows`). An optional third argument enables a debug build.
```sh
./build.sh make [platform] [debug]
```

## Future Plans

The build system will be enhanced to support automatic building of application and engine libraries, along with additional features such as hot reloading of libraries, possible integration with external profilers, and options for compiling both statically and dynamically linked versions of the executable.

In future updates, Windows-specific build and run scripts, as well as tasks, may be introduced. However, for now, Windows support remains limited to manual building and running.

For more information, please reference the [Roadmap](Roadmap.md).