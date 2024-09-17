# Miracle Framework

*"It's a miracle I actually got this far!"*

## Overview

Miracle Framework is a dynamic software framework designed to simplify the development of modular applications across multiple platforms, specifically Windows and Linux. It is designed to allow developers to create applications as dynamically loadable libraries, which in the future will facilitate hot reloading and modularity. The framework is built entirely in C, emphasizing minimal dependencies to keep the codebase lightweight and efficient.

Currently, at its core, the Miracle Framework provides mechanisms for loading and unloading libraries at runtime, and dynamically linking them at runtime. It also comes with a build system and workspace file to facilitate cross-platform development and quickly establish a working environment. The framework also comes with a demo application workspace and default required files that can be automatically copied into the parent directory using a script file.

In the future, the build system and framework itself will incorporate dynamic application and library hot reloading as a primary feature, allowing for recompilation and automatic re-linking of a program without restarting or losing the framework/application/library state.

## Design Philosophy

The framework is developed with the following principles in mind:

Minimal Dependencies: Built entirely in C with minimal external libraries, enabling developers to understand and extend the core functionality easily.
Modularity: Encourages separation of concerns by supporting dynamically loadable libraries, allowing for flexible and scalable application architectures.
Cross-Platform Support: Provides a unified API for both Windows and Linux platforms, abstracting away platform-specific complexities.
Dynamic Linking: Supports both static and dynamic linking modes, giving developers control over how libraries are integrated into their applications.
Hot Reloading: Aims to facilitate hot reloading of libraries without losing application state, enhancing development workflows and reducing downtime.


Miracle Framework is being developed entirely in C, with a focus on minimizing dependencies and external libraries. Dependencies are only included when absolutely necessary or when they offer significant efficiency, such as in cases involving proprietary hardware. This design choice enables developers to gain a deep understanding of the framework’s core functionality quickly, while also maintaining a lightweight and efficient codebase.

The framework is being built around a modular architecture, with three primary components:

- **Miracle Framework**: Serving as the core executable, this component provides the essential infrastructure for tasks such as library loading, profiling, and other shared functionalities between the engine and the application.
- **Sage Engine:** A large extension of the Miracle Framework, the Sage Engine will be designed to include shared features necessary for more complex programs. It will expand the framework's capabilities and provides a richer set of tools for developers building sophisticated applications.
- **Application:** This component is provided externally and represents the actual software that utilizes the Miracle Framework. The framework will manage the setup of the Sage Engine according to the Application's specifications.

The purpose of this approach is to maximize the amount of features that can be dynamically reloaded at runtime without losing state. 

## Usage

To get started with the Miracle Framework, add the repository as a submodule to your project, then run the internal `setup-workspace.sh` script to set up your workspace.

For more information about setting up the application, please reference [Application Setup](Application%20Setup.md). 
For information about the build process, please reference [Build System](Build%20System.md).
For information about debugging, please reference [Debugging](Debugging).

## Future Plans

### Key Planned Features

The development of Miracle Framework is currently centered on two key features:

- **Profiling Tools:** Comprehensive performance analysis tools to monitor CPU and memory usage, provide function call analysis, and track resource utilization. 
- **Hot Library Loading:** Support for dynamic library loading during runtime, while maintaining application state.

### 1.0.0 Goals

The following are the goals for Version 1.0.0 of the Miracle Framework

1. **Application Deployment:** Enable applications to be developed and launched using the Miracle Framework with minimal complexity in the design and deployment process.
2. **Accurate Profiling:** Provide precise real-time performance metrics through a robust and versatile profiling system that requires minimal changes over time.
3. **Functional Hot Loading:** Ensure seamless hot loading of the application library without affecting the application's state. The build system should also support creating statically linked libraries or disabling hot loading as needed.

For more information, please reference the [Roadmap](Roadmap.md).
