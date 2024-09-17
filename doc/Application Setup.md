## Overview

The Miracle Framework is designed to be non-intrusive, requiring minimal configuration to integrate into your project. The framework includes scripts and tools to automate the setup process, enabling you to focus on the development of your application.

## Getting Started

1. **Clone the Repository**: Add the Miracle Framework as a submodule to your project repository.
    ```bash
    git submodule add https://github.com/freshbreathmint/miracle.git miracle
	```
2. **Run the Setup Script**: Navigate to the `miracle` directory and execute the `setup-workspace.sh` script.
	```bash
	cd miracle 
	./setup-workspace.sh
	```    
	    The script will:
    
	    - Copy the `miracle.code-workspace` file into your project folder.
	    - Create the necessary directories and files required by the framework.
3. **Open the Workspace**: Use Visual Studio Code to open the `miracle.code-workspace` file and load the workspace configuration.
4. **Develop Your Application**:
    
    - Follow the framework's conventions to create your application library.
    - Use the provided APIs to manage dependencies and function calls within your libraries.
    - For a detailed example of creating an application library, refer to the [Example Application](Example%20Application.md) guide.

## Windows Setup

While native Windows development with the Miracle Framework is not currently supported, it is technically feasible. A `setup-workspace.bat` file is included for this purpose. However, you will need to manually build, run, and debug your project, as no automated build or run script is provided for Windows. Additionally, you must ensure that the correct build requirements, such as CMake, are available for the project.