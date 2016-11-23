include(ExternalProject)

# CppUnit
# This is to force rebuild if the outputs are deleted
ExternalProject_Add(
    build-cppunit
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cppunit
    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/cppunit/autogen.sh COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/cppunit/configure --prefix=${CMAKE_OUTPUT_DIRECTORY}
    BUILD_COMMAND ${MAKE}
)