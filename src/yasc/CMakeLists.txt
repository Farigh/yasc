# Target name
set(BINARY_NAME ${PROJECT_NAME})
set(LIBRARY_NAME ${PROJECT_NAME}l)

# Add current directory to include path
include_directories(.)

# Current project lib dir
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Build executable
add_executable(
    ${BINARY_NAME}
    main.cpp
)

# link with associated library
target_link_libraries(
    ${BINARY_NAME}
    ${PROJECT_NAME}l
)

# Build associated library
add_library(
    ${LIBRARY_NAME}
    SHARED
    utils/Dictionary.cpp
    utils/DynamicDictionary.cpp
)

