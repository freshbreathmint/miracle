## About

This document will serve as an opportunity to workshop and design the initial build system for Project Miracle.

## Current Development

Currently, development is focused on creating a build system around WSL (Windows Subsystem for Linux). The goal is to set up VS Code tasks to compile and run the application for both Linux and Windows environments.

### Key Challenges

1. **Interacting Between Windows and WSL:**
   - Figuring out seamless interaction between Windows and WSL is a primary challenge.
   - The file systems are separate so it's a matter of figuring out how to launch something in Windows from within WSL.
2.  **Running and Compiling:**
   - Running the application on Windows should be as simple as pressing a task button to compile and execute natively.
   - Running the Linux version of the program within WSL should ideally perform as well as running it natively on Windows, although this requires further research on executing GUI applications using WSL.
3. **Hot Reloading:**
   - Hot Reloading should function correctly when running a Windows build natively, even if it is not as critical.
   - This should not be an issue for Linux builds.

## Unorganized Ideas

1. The system should be based around the idea of application development.
   - This means that setting up a new project that uses Project Miracle as a framework should be minimally cumbersome.