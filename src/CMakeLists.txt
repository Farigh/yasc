# Target name
set(BINARY_NAME ${PROJECT_NAME})

# Add current directory as include path
include_directories(.)

# Build executable
add_executable(
    ${BINARY_NAME}
    main.cpp

    utils/Dictionary.cpp
)

