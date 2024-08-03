#!/bin/bash

echo "Running Build Script..."

# First Argument = Platform
PLATFORM=$1

# Create build directory if it doesn't exist.
mkdir -p build/$PLATFORM

# Generate build files
cmake -B build/$PLATFORM -DPLATFORM=$PLATFORM

# Build
cmake --build build/$PLATFORM