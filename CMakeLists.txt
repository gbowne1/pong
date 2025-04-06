cmake_minimum_required(VERSION 3.13)

project(pong)

# Specify compilers explicitly
set(CMAKE_C_COMPILER gcc) # Replace 'gcc' with your C compiler (e.g., clang)
set(CMAKE_CXX_COMPILER g++) # Replace 'g++' with your C++ compiler (e.g., clang++)

# SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

INCLUDE(FindPkgConfig)

# dependencie
find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

include_directories({PROJECT_NAME}
    ${SDL2_INCLUDE_DIRS}
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
)

file(GLOB_RECURSE headers src/include/*.h)
file(GLOB_RECURSE sources src/*.cpp)

add_executable(${PROJECT_NAME} ${headers} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC src/include)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL_IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
