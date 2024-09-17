# Overview

This guide provides instructions for debugging applications developed using the Miracle Framework, utilizing Visual Studio Code's integration with GDB and Valgrind. The outlined configurations and practices are designed to help developers efficiently identify and resolve issues within their projects.

The Miracle Framework's debugging setup is flexible, supporting a range of debugging needs, from breakpoints and variable inspections to advanced memory checks with Valgrind. Custom launch configurations and tasks in Visual Studio Code allow seamless integration with the GNU Debugger (GDB) and Valgrind.

### Prerequisites

Before you begin debugging, ensure you have the following tools installed:
- **GDB**
- **Valgrind**

## Launch Configurations

Below are the debug configurations included in the `launch.json` file.

### [LINUX] GDB

This configuration is designed for standard debugging using GDB within Visual Studio Code. It allows you to launch your program directly in the debugger, currently running in the internal console by default. This setup is primarily intended for use in WSL environments, where external consoles are not fully supported. However, if you are working in a native Linux environment, you can modify this configuration to launch in an external console by setting `externalConsole` to `true`.

### [LINUX] GDB + Valgrind

This configuration combines the power of GDB with Valgrind to detect and debug memory-related issues, such as leaks or illegal memory access, during your debugging session. Valgrind is launched in GDB server mode, and GDB automatically attaches to it, enabling real-time memory checking alongside traditional debugging.

##### **Important Considerations:**
- **Performance Impact:** Programs running under Valgrind are *significantly slower* than usual due to the extensive memory checks and analysis being performed. This slowdown is normal and expected but should be taken into account when debugging performance-sensitive applications.
- **Multiple Valgrind Instances:** If multiple instances of Valgrind are running, this configuration may not work as intended and could default to launching in the internal console without Valgrind integration. To address this, a post-debug task has been included to automatically terminate all Valgrind instances after the debugging session, ensuring a clean state for future debugging.

## Future Enhancements

As the Miracle Framework evolves, the debugging configurations will be expanded to support a wider range of development environments and tools. Planned enhancements include:

- **Native Windows Debugging Support:** The introduction of debugging setups tailored specifically for native Windows development. This will allow seamless debugging experiences across both Linux and Windows platforms, accommodating developers working in different environments.
- **Expanded External Tool Integration:** Building on the current Valgrind support, additional external tools may be integrated into the debugging process. These tools could include performance profilers, static analyzers, and other utilities to enhance the debugging and optimization workflow.