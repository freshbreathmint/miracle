# Overview 

The **Miracle Framework Extension** integrates Miracle framework build, run, and configuration management directly into Visual Studio Code. This extension provides the following features:

- **Project Configuration Tree**: View and edit project configurations in an intuitive tree view. Allows editing of individual entries. A dedicated button to Add Dependencies to a library or the application is also provided.
- **Framework Actions**: Easily trigger custom Build/Run actions and use scripts to clean the build/bin libraries or set up the application folder.
- **Hot Compilation Support**: Hot Compile individual libraries or all of the dynamic libraries in the project at once. 
- **Quick Library Add**: Quickly add a new library and automatically add template files.

## Installation

1. Install the extension from the VSCode marketplace.
2. Ensure you have Git and Python installed and accessible in your system `PATH`.
3. Set up your project by initializing a git repo in your project folder and selecting `Setup Workspace` under Framework Actions.

# Features

## Project Configuration

The **Project Configuration Tree** allows you to view and manage your project's configuration via the `config.ini` file.

### Commands

- **Add Library**: Add a new library to your project and configure it using the `setup.py` script.
- **Edit INI Value**: Edit configuration values directly from the tree view.
- **Add Dependency**: Add dependencies to specific sections (e.g., application or library) in the `config.ini` file.
- **Hot Compile**: Compile the application or a selected library with a timestamp.

## Build Panel

The build panel provides options to build, run, and configure your project. Access it by clicking on the **Actions** tab in the **Miracle Framework** activity bar.

### Build Executable

The **Build Executable** action allows you to compile your project by selecting the platform, link type, and build type.

**Platform Options**:
- `Windows`
- `Linux`

**Link Type Options**:
- `Dynamic` Libraries will be dynamically loaded at runtime.
- `Static` Libraries will be statically linked at compile time.

**Build Type Options**:
- `Debug`
- `Release`

To build, select your options and click `Build Executable`.

### Full Hot Compile

Perform a full hot compile by selecting the platform (Windows or Linux), and then clicking `Full Hot Compile`. This action compiles the application and all other dynamic libraries with timestamps. 

### Run Executable

After building the executable, you can run it by selecting the platform and build type. Click `Run Executable` to launch the app within the VSCode terminal. You can select which platform and build type to search for the executable in.

### Framework Actions

- **Clean Build Directories**: Cleans up the generated build directories.
- **Setup Workspace**: Automatically set up your workspace by adding the framework as a Git submodule and running the `setup.py` script, prompting you for relevant information about your project.

## Command Palette

The following commands are available and can be executed via the command palette (`Ctrl + Shift + P`):

- `Miracle: Refresh INI Tree`: Refresh the INI tree view to reflect changes in the configuration.
- `Miracle: Edit INI Value`: Edit the value of a selected INI key.
- `Miracle: Add Dependency`: Add a dependency to the `application` or a specific library.
- `Miracle: Add Library`: Add a new library to the project configuration.
- `Miracle: Hot Compile`: Perform a hot compile for the application or selected library.
- `Miracle: Build Executable`: Build the application executable.
- `Miracle: Full Hot Compile`: Execute a full hot compile for all targets.
- `Miracle: Run Executable`: Run the built executable.
- `Miracle: Clean Build Directories`: Clean up the build directories in the workspace.

## Setup Workspace

To set up your workspace for the first time:

1. Open your project in VSCode.
2. Initialize a git repo if one does not already exist in the project folder.
3. In the **Actions** panel, click **Setup Workspace**.
4. The extension will check if the `miracle` framework is already installed as a Git submodule. If not, it will add it for you.
5. You will be prompted to enter a project name.
6. After setup, the workspace will automatically load the necessary configurations and copy application template files.

## Requirements

Make sure the following dependencies are available on your system:

- **Git**: Required.
- **Python**: Used for running scripts.

