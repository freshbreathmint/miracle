# Overview

The Miracle Framework is designed to be non-intrusive, requiring minimal setup. You can set up your application and project by running a single script.

Currently, you can set up the application folder using the `setup-workspace.sh` script. This script copies the `miracle.code-workspace` file into your project folder. After running the script, open the workspace file in Visual Studio Code.

In the future, this script will also automatically create any necessary directories or files required by the Miracle Framework. For more information, please reference the [Roadmap](Roadmap.md).

## Windows Setup

Development using Miracle Framework on native Windows is not currently supported, but is technically possible. Because of this, a setup file `setup-workspace.bat` has been provided. You will need to build/run/debug manually yourself, as no build or run script is provided. You will also be responsible for providing the proper build requirements for using CMake.