# Miracle Framework

*"It's a miracle any of this works!"*

## Overview

The Miracle Framework is a software development framework designed to offer flexibility, modularity, and cross-platform compatibility. 

Miracle Framework is cross-platform, abstracting away differences between Windows and Linux. This simplifies development, allowing developers to focus on building their application without worrying about platform-specific details.

Users can dynamically define new libraries in the configuration file, specifying each as either "static" or "dynamic." Dynamic libraries are compiled as shared libraries and can depend on other dynamic libraries. These dependencies are automatically resolved at runtime through a built-in function that registers and resolves function pointers when a library is loaded. In the future, this feature will be extended to support reloading libraries at runtime to replace old ones without restarting the application.

The framework offers both static and dynamic compilation, allowing developers to create fully static binaries or leverage the aforementioned dynamic loading system as needed. 

Once hot reloading is fully implemented, and the framework can be considered stable, development will begin on an application utilizing the Sage Engine (a game engine that will be built as a dynamic library for the framework). At that point, the framework will be released as version 1.0.0, and further applications will be developed to help extend the framework's capabilities.

## Design

The Miracle Framework is developed with a strong emphasis on modularity, cross-platform support, and extensibility. Its architecture allows for flexible management of libraries, supporting both dynamic and static loading to suit a wide range of project needs.

### Architecture & Dependency Structure

The Miracle Framework treats the application as a dynamic library that is loaded last and contains the program’s entry point. The modular system architecture is designed as follows:

- **Dynamic Libraries** are loaded at runtime. They may depend on other dynamic libraries, with the framework automatically resolving dependencies when they are loaded.
- **Static Libraries** are compiled directly into the application or other dynamic libraries.

This structure enables a modular approach to development, where components can eventually be compiled and loaded individually during runtime. The application can also be compiled into a fully static executable for release builds if needed.

### Miracle Core Library

The **Miracle Core** library is a static library linked automatically with every dynamic library, the application, and the framework executable. It provides essential shared functions such as data structures and framework-specific utilities.

### Sage Engine

The **Sage Engine** is a planned game engine built on top of the Miracle Framework. It will offer a robust set of tools for game development, including state management and rendering systems. When creating a new application through the framework's Visual Studio Code extension, users will have the option to automatically include the Sage Engine in their project.

## Usage

To get started with the Miracle Framework:

1. **Download the Extension**: Install the Miracle Framework extension for Visual Studio Code.
2. **Set Up the Workspace**: Press "Setup Workspace" to automatically create a default application in your project folder and clone the framework as a submodule.
3. **Develop Your Application**: Use the "Add Library" feature in the extension to add static or dynamic libraries as needed, and configure them using the configuration editor.

For more details on using the Miracle Framework extension, see the [VSC Extension Guide](doc/VSC%20Extension.md).

## Current State

Significant progress has been made, with core mechanisms for dynamic library loading, function resolution, and cross-platform support implemented in a basic form. The next development phase will focus on implementing the hot reloading feature and beginning development on the Sage Engine.

## Future Plans

### Key Planned Features

- **Hot Library Loading:** Add support for dynamically reloading libraries at runtime, maintaining state and updating dependent libraries.
- **Sage Engine Integration:** Enable seamless integration of the Sage Engine during application setup.
- **Logging & Profiling:** Implement systems for memory management, profiling, and logging.

### 1.0.0 Goals

Key objectives for version 1.0.0 of the Miracle Framework include:

1. **Application Deployment:** Ensure applications can be developed and deployed easily without issues.
2. **Functional Hot Loading:** Implement smooth hot reloading of libraries while preserving state and updating dependent libraries.

For more details on future features and development plans, see the [Roadmap](Roadmap.md).