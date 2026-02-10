cmake_minimum_required(VERSION 3.16)

project(EcoSystem
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------
# AUTOMATSKO SKUPlJANJE .cpp FAJLOVA
# -----------------------------
# uzima sve cpp iz src/ i podfoldera, uključujući src/raylib
file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
    src/raylib/*.cpp
)

# -----------------------------
# EXECUTABLE
# -----------------------------
add_executable(EcoSystem ${PROJECT_SOURCES})

# -----------------------------
# INCLUDE PATHS
# -----------------------------
target_include_directories(EcoSystem
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/raylib
        ${CMAKE_SOURCE_DIR}/lib/raylib/include
)

# -----------------------------
# LINK LIBRARIES
# -----------------------------
target_link_directories(EcoSystem PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/raylib/lib
)

target_link_libraries(EcoSystem PRIVATE
    raylib
    winmm
    gdi32
    opengl32
    kernel32
    user32
    shell32
)

# -----------------------------
# ASSETS
# -----------------------------
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# -----------------------------
# OUTPUT DIRECTORY
# -----------------------------
set_target_properties(EcoSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/Windows
)
