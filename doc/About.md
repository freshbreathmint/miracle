# Project Miracle

## Overview

Project Miracle is a planned software framework aimed at providing essential tools that are universally useful for developing applications. The motivation of developing this software is to make the process of designing software simpler for myself and others. 

## Key Planned Features

- **Full Profiling:** Comprehensive performance analysis tools that monitor CPU and memory usage, provide function call analysis, and resource utilization. 
- **Hot Library Loading:** Support for dynamic library loading during runtime, while maintaining application state.

## 1.0.0 Goals

Here are the following goals for version 1.0.0 of this project:

1. **Application Deployment:** Applications may be launched using the framework. The process for designing and deploying an application that uses the framework should be minimally cumbersome.
2. **Accurate Profiling:** The profiler provides precise performance metrics in real-time. The underlying system should be designed to be robust and versatile, requiring minimal changes over time.
3. **Functional Hot Loading:** The application should be able to seamlessly hot load it's library without effecting the state of the application. The build system should also support creating statically linked libraries or disabling hot loading as needed.