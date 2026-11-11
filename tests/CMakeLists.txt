include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
    GIT_SHALLOW    TRUE
)
# MSVC: link the C runtime the same way as the rest of the project (/MD).
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(lattice_tests
    Logging/LoggerTests.cpp
)
target_link_libraries(lattice_tests PRIVATE Lattice::Core GTest::gtest_main lattice_warnings)

include(GoogleTest)
gtest_discover_tests(lattice_tests)
