# Target name
set(BINARY_NAME ${PROJECT_NAME})
set(LIBRARY_NAME ${PROJECT_NAME}l)

# Project root include dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

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

    # dict
    dict/Dictionary.cpp
    dict/DictionaryFactory.cpp
    dict/DynamicDictionary.cpp

    # lang
    lang/DelimitedLanguageRegister.cpp
    lang/LanguageSeparator.cpp

    # utils
    utils/YascGetopts.cpp
    utils/YascOption.cpp
)

