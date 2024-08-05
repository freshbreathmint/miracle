#!/bin/bash

echo "Running build script..."

# Variables
ACTION=$1
PLATFORM=$2

# Function to clean build and bin directories
clean() {
    echo "Cleaning build and bin directories..."
    rm -rf build bin
    echo "Clean complete."
}

# Function to build for a specified platform
make() {
    # Check if platform variable was specified
    if [ -z "$PLATFORM" ]; then
        echo "Error: No platform specified. Please specify a platform such as [native|windows]."
        exit 1
    fi
    
    # Create build directory if it doesn't already exist
    mkdir -p build/$PLATFORM
    
    # Generate build files for the specified platform
    case $PLATFORM in
        windows)
            cmake -B build/$PLATFORM -DCMAKE_TOOLCHAIN_FILE=windows.cmake -DPLATFORM=$PLATFORM
            ;;
        native)
            cmake -B build/$PLATFORM -DPLATFORM=$PLATFORM
            ;;
        *)
            echo "Error: Unsupported platform specified. Please specify [native|windows]."
            exit 1
            ;;
    esac

    # Build executable
    cmake --build build/$PLATFORM
    echo "Build for platform '$PLATFORM' complete."
}

# Execute arguments
case $ACTION in
    make)
        make
        ;;
    clean)
        clean
        ;;
    *)
        echo "Invalid action. Use 'make' followed by a platform to build, or 'clean' to clean the build files."
        exit 1
        ;;
esac