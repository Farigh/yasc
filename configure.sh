#! /bin/bash

# Default options
BUILD_DIR="build/"
CMAKE_GENERATOR="Unix Makefiles"
BUILD_TYPE="Release"
CMAKE_OPTIONS="-LAH -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_COLOR_MAKEFILE=ON"

# Create build directory
if [ ! -d "./$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi


# Configure project
cd $BUILD_DIR
cmake -G "$CMAKE_GENERATOR" -DCMAKE_BUILD_TYPE=$BUILD_TYPE $CMAKE_OPTIONS ..

if [ $? -eq 0 ]; then
    echo "Project configured successfully."
    echo "To build the project, use the following command:"
    echo "  cmake --build $BUILD_DIR"
else
    echo "Project configuration failed.";
fi
