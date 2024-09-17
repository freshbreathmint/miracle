# Miracle Framework

*"It's a miracle I actually got this far!"*

## Overview

The Miracle Framework is a versatile software framework developed to simplify the creation of modular applications across multiple platforms, specifically Windows and Linux. It enables developers to design applications as dynamically loadable libraries, paving the way for future support of hot reloading and modularity. Built entirely in C, the framework minimizes external dependencies, promoting a lightweight and efficient codebase.

At its core, the Miracle Framework provides mechanisms for loading and unloading libraries at runtime and dynamically linking them. It also includes a build system and workspace setup to support cross-platform development, enabling developers to quickly establish a working environment. Additionally, it offers a demo application workspace with default files that can be automatically copied into the parent directory using an included script.

In the future, the build system and framework will support dynamic application and library hot reloading as a key feature, allowing for recompilation and automatic re-linking without restarting or losing the state of the framework, application, or libraries.

## Design Philosophy

The framework is developed with the following core principles:

- **Minimal Dependencies:** Developed entirely in C with minimal reliance on external libraries, ensuring ease of understanding and extensibility for developers.
- **Modularity:** Supports dynamically loaded libraries, allowing dependencies on other dynamically loaded libraries and encouraging a modular approach.
- **Cross-Platform Support:** Offers a unified API for both Windows and Linux platforms, abstracting away platform-specific differences and simplifying cross-platform development with provided build scripts.
- **Dynamic Linking:** Supports both static and dynamic linking, enabling release builds to be statically compiled while retaining the ability to hot load libraries during development.
- **Hot Reloading:** Future versions will support hot reloading of libraries without losing the application or library state, improving development workflows by minimizing downtime.

The framework follows a modular architecture, with several key components:

- **Miracle Framework**: Manages library loading, function binding, and provides shared functionality between libraries and applications.
- **MiracleLib**: A core library that is statically linked with all components compiled to work with the Miracle Framework. Currently, it includes dynamic arrays but will be expanded in the future to incorporate additional data structures and useful functions, offering developers foundational tools that can be used across different libraries.
- **Sage Engine:** An extension of the Miracle Framework, designed to provide additional features required for more complex applications. Currently, it serves as an example library for development purposes.
- **Application:** The user-created application that utilizes the Miracle Framework, and optionally the Sage Engine, to develop specific features.
## Current State

Significant progress has been made on the project. The core mechanisms for dynamic library loading, function resolution, and cross-platform support have been implemented in a basic form. With some adjustments, the framework can already be used to load and connect different libraries automatically.

## Usage

To get started with the Miracle Framework:

1. **Clone the Repository**: Add the framework to your project as a submodule.
2. **Set Up the Workspace**: Run the provided `setup-workspace.sh` script to configure your development environment.
3. **Develop Your Application**: Create your application as a dynamically loadable library, using the framework’s APIs to manage dependencies and function calls.

For detailed setup instructions, refer to the [Application Setup](Application%20Setup.md) guide. For build instructions, see the [Build System](Build%20System.md) documentation.

## Future Plans

### Key Planned Features

- **Profiling Tools**: Integrate performance analysis tools to monitor CPU and memory usage across libraries, analyze function calls, and track resource utilization.
- **Hot Library Loading:** Introduce support for dynamic library loading at runtime while maintaining library state.
- **Custom Application Building:** Specify the build details of the application using an initialization file, allowing for easy use of the Framework's core features.

### 1.0.0 Goals

The following are the key objectives for Version 1.0.0 of the Miracle Framework:

1. **Application Deployment:** Streamline the development and deployment of applications using the Miracle Framework, minimizing complexity.
2. **Accurate Profiling:** Provide real-time performance metrics through a robust profiling system that requires minimal updates over time.
3. **Functional Hot Loading:** Ensure smooth hot loading of the application library without affecting the state of related libraries.

For further details on future features and development plans, see the [Roadmap](Roadmap.md).
