set (TEST_NAME YascUnitTestRunner)

# Add current directory to include path
include_directories(.)

# Project root include dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

# Third-parties include dir
include_directories(${CMAKE_OUTPUT_DIRECTORY}/include)

# Third-parties lib dir
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(
    ${TEST_NAME}
    EXCLUDE_FROM_ALL
    main.cpp

    tests/DataManager.cpp

    # Helpers
    helpers/cppunit/YascTestSuiteManager.cpp
    helpers/cppunit/YascTestRunner.cpp

    # Tests
    tests/dict/DictionaryFactoryTest.cpp
    tests/dict/DictionaryTest.cpp
    tests/dict/DynamicDictionaryTest.cpp
)

# Add needed libs
target_link_libraries(
    ${TEST_NAME}
    ${PROJECT_NAME}l
    cppunit
)

add_dependencies(${TEST_NAME} build-cppunit ${PROJECT_NAME})

# Allow test reserved target overload
if(POLICY CMP0037)
    cmake_policy(PUSH)
    cmake_policy(SET CMP0037 OLD)
endif(POLICY CMP0037)

# Add custom test target
add_custom_target(test
                  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/unit_test_runner.sh ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}
                  DEPENDS ${TEST_NAME})

# Restore policy
if(POLICY CMP0037)
    cmake_policy(POP)
endif(POLICY CMP0037)