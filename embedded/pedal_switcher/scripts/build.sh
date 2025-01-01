#!/bin/bash

# Create a build directory if it doesn't exist
mkdir -p build

# Run CMake to configure the project
cmake -S app -B build

# Build the project
make -C build
