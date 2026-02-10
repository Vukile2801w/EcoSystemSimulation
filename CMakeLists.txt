cmake_minimum_required(VERSION 3.16)

project(EcoSystem
    VERSION 0.1
    LANGUAGES CXX
)

# -----------------------------
# C++ STANDARD
# -----------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------
# AUTOMATSKO SKUPlJANJE .cpp FAJLOVA
# -----------------------------
file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
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
        ${CMAKE_SOURCE_DIR}/lib/raylib/include
)

# -----------------------------
# LIBRARIES (primeri)
# -----------------------------
# target_link_libraries(EcoSystem
#     PRIVATE
#         user32
#         opengl32
# )

# Ako imaš .lib fajlove:
target_link_directories(EcoSystem PRIVATE
 ${CMAKE_SOURCE_DIR}/lib/raylib/lib
)

# link lib files
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
# OUTPUT DIRECTORY
# -----------------------------
set_target_properties(EcoSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/Windows
)
