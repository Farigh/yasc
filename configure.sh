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
cmake_result=$?
cd -

if [ $cmake_result -ne 0 ]; then
    echo "Error: cmake generation failed, see above"
    exit 1
fi

if [ $? -eq 0 ]; then
    echo "Project configured successfully."

    echo -n "Generating root Makefile..."
    cat <<EOF > Makefile
.SILENT:

all:
	cmake --build $BUILD_DIR

%:
	make -C $BUILD_DIR \$*

EOF
    echo "Done"
    echo "To build the project, use the following command:"
    echo '   $ make'
else
    echo "Project configuration failed.";
fi
