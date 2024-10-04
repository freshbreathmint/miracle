# Miracle Framework

*"It's a miracle any of this works!"*

## Overview

The Miracle Framework is a versatile, modular software development framework designed to provide flexibility, cross-platform compatibility, and dynamic functionality. Its core philosophy focuses on delivering a development environment where components can be linked both statically and dynamically, allowing developers to choose the best approach for their project needs.

The framework supports defining new libraries dynamically through a project configuration file. Each library can be set as static or dynamic. Dynamic libraries are compiled as shared libraries, with dependencies automatically resolved at runtime using the framework’s built-in function resolution API. This API registers and resolves function pointers whenever a library is loaded. Future updates will expand this system to support hot reloading, enabling developers to reload libraries at runtime without restarting the application, while maintaining proper updates for dependent libraries. Static libraries, on the other hand, are linked traditionally at compile time to libraries that specify it as a dependency.

Miracle Framework is designed for flexibility, offering both fully static binaries and a dynamic loading system for modular applications. It also automates aspects of release builds, such as naming binaries according to the application and embedding a custom icon in Windows executables.

Once hot reloading is fully implemented, the framework will be considered stable, with version 1.0.0 marking its official release. From that point, work will also begin on developing the **Sage Engine**—a game engine built on the Miracle Framework. Future development will focus on expanding both the framework's capabilities and the Sage Engine by developing various applications and games.

## Details

The Miracle Framework is developed with a strong emphasis on modularity, cross-platform support, and extensibility. Its architecture allows for flexible management of libraries, supporting both dynamic and static loading to suit a wide range of project needs.

## Architecture & Dependency Structure

The Miracle Framework treats the application itself as a dynamic library loaded at runtime. This creates a system where the application, dynamic libraries, and static libraries interact in a modular, layered manner:

- **Dynamic Libraries**: Loaded during runtime and capable of depending on other dynamic libraries. The framework handles dependency resolution automatically, registering and resolving function pointers as needed.
- **Static Libraries**: Linked directly to either the application or other dynamic libraries during the compile phase.

This architecture allows for an approach where components can be individually developed and loaded dynamically at runtime, or alternatively, compiled into a fully static executable.

### Miracle Core Library

**Miracle Core** is a static library utilized by dynamic libraries, the application, and the framework, providing essential utilities such as data structures and internal functionality such as the function resolution API.

### Sage Engine

The **Sage Engine** is an in-development game engine built on top of the Miracle Framework. Its goal is to provide a rich set of tools tailored for game development, including features for rendering, input handling, state management, and more. Future versions of the Miracle Framework Visual Studio Code extension will enable automatic integration of the Sage Engine into new projects.

## Usage

To get started with the Miracle Framework:

1. **Download the Extension**: Install the Miracle Framework extension for Visual Studio Code.
2. **Initialize a Repo**: Initialize a git repo in the project folder.
3. **Set Up the Workspace**: Press "Setup Workspace" to automatically create a default application in your project folder and clone the framework as a submodule.
4. **Develop Your Application**: Use the "Add Library" feature in the extension to add static or dynamic libraries as needed, and configure them using the configuration editor.

For more details on using the Miracle Framework extension, see the [VSC Extension Guide](doc/VSC%20Extension.md).

## Current State

Significant progress has been made, with core mechanisms for dynamic library loading, function resolution, and cross-platform support implemented. The next development phase will focus on implementing the hot reloading feature and beginning development on the Sage Engine.

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