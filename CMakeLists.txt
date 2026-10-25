cmake_minimum_required(VERSION 3.20)

project(Lattice
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lattice_app src/main.cpp "src/Core/include/LatticeSingleton.h" "src/Core/include/Logger/LatticeLogger.h" "src/Core/source/Logger/LatticeLogger.cpp" "src/Core/include/Logger/Sink/LogSink.h" "src/Core/include/Logger/Sink/ConsoleSink.h" "src/Core/source/Logger/Sink/ConsoleSink.cpp" "src/Core/source/Logger/Sink/LogSink.cpp" "src/Core/include/Logger/LogLevel.h" "src/Core/include/Logger/LogCategory.h" "src/Core/include/LatticeAssert.h")