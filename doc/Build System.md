## Overview

The Miracle Framework provides a flexible build system designed to streamline the development process across different platforms. It leverages CMake for cross-platform build generation and integrates with Visual Studio Code tasks for ease of use.

## Requirements

- **Operating System**:
    - **Linux**: Native Linux environment or Windows Subsystem for Linux (WSL).
    - **Windows**: Native Windows development is supported but may require manual configuration.
- **Compilers**:
    - `gcc` for Linux builds.
    - `x86_64-w64-mingw32-gcc` for cross-compiled Windows builds.
- **CMake:** Version 3.30 or higher.
- **Visual Studio Code**: With recommended extensions installed.

## Build System Details

The Miracle Framework build system is centered around a **build script** (`build.sh`), which simplifies the process of configuring, building, and cleaning projects for both Linux and Windows platforms. Additionally, Visual Studio Code tasks have been integrated to make the build process more accessible directly from the editor.

### Visual Studio Code Integration

The build system integrates with **Visual Studio Code tasks**, allowing users to perform common build actions without leaving the editor. Through the tasks accessible in the status bar, users can execute various commands such as:

- **Clean Build Directories:** This task cleans the build and binary directories to prepare for a fresh build.
- **Build & Run**: Self explanatory, cross compilation is also available, and cross-compiled binaries can automatically be run using WSL.
- **Generate Release Build:** Generate a statically linked build of the executable.

### Build Script Overview

The `build.sh` script is designed to streamline the build process by handling platform-specific configurations for both Linux and Windows environments. It supports actions such as cleaning build directories and building the project with optional flags for static or dynamic linking, as well as debug builds. This flexibility allows developers to tailor the build process to their specific needs, whether for development or release.

#### Usage:

- **Clean Directories:** This command removes the existing build and binary directories (`/build` & `/bin`), ensuring a clean build environment.
```sh
./build.sh clean
```
- **Build Project**: This command generates the necessary build files using CMake and compiles the project for the specified platform (`linux` or `windows`). It also provides optional flags to enable static or dynamic linking and to perform debug builds.
```sh
./build.sh make [platform] [linking] [debug]
```   
- `[platform]`: Specifies the target platform (`linux` or `windows`).
- `[linking]`: Specifies whether to use static or dynamic linking (`static` or `dynamic`).
- `[debug]`: Optional flag to specify whether to build in debug mode. Omit for a release build.

## Future Plans

In future versions, the build script will support additional automation, such as adjusting executable names and linked libraries based on an initialization file provided by the application library. This will allow the build process to be dynamically tailored to the needs of each application, reducing manual configuration and enhancing overall efficiency. The build script and tasks will be reworked again to be built around easy and quick hot reloading when that feature is added. Windows-specific build and run scripts, as well as tasks, may be introduced. However, for now, Windows support remains limited to manual building and running.

For more information, please reference the [Roadmap](Roadmap.md).