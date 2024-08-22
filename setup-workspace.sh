#!/bin/bash

echo "Making directories..."
mkdir -p ../src

echo "Copying Workspace file..."
cp "application/miracle.code-workspace" "../"
echo "Workspace file copied. Please open the workspace in Visual Studio Code."