# ---- Core library -----------------------------------------------------------
add_library(lattice_core STATIC
    Core/source/Logging/Logger.cpp
    Core/source/Logging/Sink/ConsoleSink.cpp
)
add_library(Lattice::Core ALIAS lattice_core)

target_include_directories(lattice_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
)
target_compile_features(lattice_core PUBLIC cxx_std_20)
target_compile_definitions(lattice_core PUBLIC
    $<$<CONFIG:Debug>:LATTICE_DEBUG>
)
target_link_libraries(lattice_core PRIVATE lattice_warnings)

# ---- Sandbox application ----------------------------------------------------
add_executable(lattice_app main.cpp)
target_link_libraries(lattice_app PRIVATE Lattice::Core lattice_warnings)
