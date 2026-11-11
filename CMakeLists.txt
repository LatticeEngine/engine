cmake_minimum_required(VERSION 3.20)

project(Lattice
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LATTICE_BUILD_TESTS "Build Lattice unit tests" ON)
option(LATTICE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(LATTICE_BUILD_DOCUMENTATION "Build the documentation (requires Doxygen and Graphviz)" OFF)

# Shared compiler warnings, applied to every Lattice target.
add_library(lattice_warnings INTERFACE)
if(MSVC)
    target_compile_options(lattice_warnings INTERFACE /W4 /permissive- /utf-8)
    if(LATTICE_WARNINGS_AS_ERRORS)
        target_compile_options(lattice_warnings INTERFACE /WX)
    endif()
else()
    target_compile_options(lattice_warnings INTERFACE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
    if(LATTICE_WARNINGS_AS_ERRORS)
        target_compile_options(lattice_warnings INTERFACE -Werror)
    endif()
endif()

add_subdirectory(src)

if(LATTICE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(LATTICE_BUILD_DOCUMENTATION)
    # "dot" is the Graphviz program that draws the diagrams.
    find_package(Doxygen REQUIRED COMPONENTS dot)

    set(DOXYGEN_UML_LOOK YES)
    # The code is barely commented yet: document everything, private members included.
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

    doxygen_add_docs(lattice_docs
        ${CMAKE_CURRENT_SOURCE_DIR}/README.md
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        COMMENT "Generating documentation"
    )
endif()
