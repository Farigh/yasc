set (TEST_NAME YascUnitTestRunner)

# Add current directory to include path
include_directories(.)

# Third-parties include dir
include_directories(${CMAKE_OUTPUT_DIRECTORY}/include)

# Third-parties lib dir
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(
    ${TEST_NAME}
    main.cpp
)

# Add needed libs
target_link_libraries(
    ${TEST_NAME}
    cppunit
)

add_dependencies(${TEST_NAME} build-cppunit)

# Add test target
add_custom_target(test
                  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/unit_test_runner.sh ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}
                  DEPENDS ${TEST_NAME})
