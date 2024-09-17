#!/bin/bash

echo "Making directories..."
mkdir -p ../src
mkdir -p ../include
mkdir -p ../.vscode

echo "Copying files..."
cp "application/miracle.code-workspace" "../"
cp "application/.vscode/c_cpp_properties.json" "../.vscode/"
cp "application/include/entry.h" "../include/"
cp "application/include/libapi.h" "../include/"
cp "application/include/libapi_dynamic.h" "../include/"
cp "application/src/entry.c" "../src/"

echo "Files copied. Please open the workspace in Visual Studio Code."