cmake_minimum_required(VERSION 3.14)
project(PongGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow user to manually set SDL2_DIR if needed
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# --- SDL2 and dependencies ---
# Try config-mode first
find_package(SDL2 CONFIG QUIET)
find_package(SDL2_image CONFIG QUIET)
find_package(SDL2_ttf CONFIG QUIET)

# If not found, try pkg-config (Linux/macOS fallback)
if (NOT SDL2_FOUND OR NOT SDL2_image_FOUND OR NOT SDL2_ttf_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)
    pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)
endif()

# Collect include directories and libraries
if (SDL2_FOUND)
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR})
    set(SDL2_LIBRARIES ${SDL2_LIBRARIES} SDL2::SDL2)
endif()
if (SDL2_image_FOUND)
    set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})
    set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARIES} SDL2_image::SDL2_image)
endif()
if (SDL2_ttf_FOUND)
    set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
    set(SDL2_TTF_LIBRARIES ${SDL2_TTF_LIBRARIES} SDL2_ttf::SDL2_ttf)
endif()

# --- Directories ---
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    src/include
)

# --- Source Files ---
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- Executable ---
add_executable(Pong ${SOURCES})

# --- Link SDL2 ---
target_link_libraries(Pong
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
