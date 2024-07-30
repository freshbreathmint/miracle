# Miracle Framework

*"It's a miracle that I've worked on it at all!"*

## Overview

Miracle Framework is an in-development software framework aimed at providing essential tools universally useful for developing applications. The motivation behind developing this software is to ease the process of designing and deploying software applications for myself and others.

## Design Philosophy

Miracle Framework is coded entirely in C, using minimal dependencies and libraries, except where necessary or most efficient, such as interfacing with proprietary hardware. This approach enables a deep understanding of the framework's inner workings for developers and promotes a lightweight and efficient codebase.

The framework is planned to be built around a modular architecture, comprising three main components:

- **Miracle Framework**: Acting as the executable portion, the framework will provide the necessary infrastructure for library loading, profiling, and other shared functionalities between the engine and the application.
- **Sage Engine:** Essentially a modular state machine that can be customized and initialized by the application according to it's requirements.
- **Application:** Provided externally, this library will represent the actual software utilizing the framework.

In the future, the engine element of the framework will include components like a rendering backend, window management, input handling, and event systems. However, the current focus is on developing the core framework functionality and enabling application loading through the framework. This phased approach ensures a focused and manageable development process.

The framework aims to allow applications to specify required engine components at startup, such as a rendering backend and window management, while excluding unnecessary elements. This flexibility aims to ensure that both the engine and the application can be modified, recompiled, and hot reloaded while maintaining state.

## Key Planned Features

The development of Miracle Framework is currently centered on two key features:

- **Full Profiling:** Comprehensive performance analysis tools to monitor CPU and memory usage, provide function call analysis, and track resource utilization. 
- **Hot Library Loading:** Support for dynamic library loading during runtime, while maintaining application state.

## 1.0.0 Goals

The following are the goals for Version 1.0.0 of the Miracle Framework

1. **Application Deployment:** Enable applications to be developed and launched using the Miracle Framework with minimal complexity in the design and deployment process.
2. **Accurate Profiling:** Provide precise real-time performance metrics through a robust and versatile profiling system that requires minimal changes over time.
3. **Functional Hot Loading:** Ensure seamless hot loading of the application library without affecting the application's state. The build system should also support creating statically linked libraries or disabling hot loading as needed.

For more information, please reference the [Roadmap](Roadmap.md).
