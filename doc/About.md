# Project Miracle

*"It'll be a miracle if this ever gets done!"*

## Overview

Project Miracle is a planned software framework aimed at providing essential tools universally useful for developing applications. The motivation behind developing this software is to simplify the process of designing software for myself and possibly others. 
## Design Philosophy

Project Miracle will be coded in C. It should use minimal dependencies/libraries, except where necessary, such as interfacing with proprietary hardware or in cases where it makes the most sense.

Currently, the scope is limited to enabling profiling and hot loading. However, future expansions may include rendering backends, window management, logging, input handling, event systems, and more. It's also possible that some or all of those features will be wrapped inside of a different program.

During development, it's important to consider:

- Is the program doing anything unnecessary for the application?
- Are there systems being enabled/set up that aren't explicitly required by the application?

These concerns should be addressed at the start when the application begins to interface with the framework, potentially through a modular system.

## Key Planned Features

- **Full Profiling:** Comprehensive performance analysis tools to monitor CPU and memory usage, provide function call analysis, and resource utilization. 
- **Hot Library Loading:** Support for dynamic library loading during runtime, while maintaining application state.

## 1.0.0 Goals

Here are the following goals for version 1.0.0 of this project:

1. **Application Deployment:** Applications can be launched using the framework. The process for designing and deploying an application using the framework should be minimally cumbersome.
2. **Accurate Profiling:** The profiler provides precise performance metrics in real-time. The underlying system should be robust and versatile, requiring minimal changes over time.
3. **Functional Hot Loading:** The application should be able to seamlessly hot load it's library without effecting the state of the application. The build system should also support creating statically linked libraries or disabling hot loading as needed.