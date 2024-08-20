# Miracle Framework

*"It's a miracle that anything I made here works!"*

## Overview

Miracle Framework is an evolving software framework designed to offer a comprehensive set of tools for application development. The primary goal of this framework is to simplify the process of designing, building, and deploying software, making it accessible and efficient for both myself and other developers.

At its current stage, Miracle Framework operates as an advanced build system. It streamlines the setup process, allowing users to quickly establish a working environment. This means developers can focus more on writing code and less on the often cumbersome tasks of configuring build systems and other initial setup procedures.

Looking ahead, the framework is planned to be expanded with capabilities for creating applications as dynamically loadable libraries. This system will allow not only the core application libraries but also additional dependencies to be loaded on demand, offering enhanced modularity and flexibility. As more tools and features are incorporated, Miracle Framework will hopefully evolve into a robust and versatile platform, tailored for comprehensive software development.

## Design Philosophy

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
