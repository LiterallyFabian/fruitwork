#
# Use the Makefile instead of this script.
# This is not maintained and only used for CLion to find the source files.
#

cmake_minimum_required(VERSION 3.22)
project(fruitwork)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR C:/msys64/mingw64/include)
set(SDL2_LIB_DIR C:/msys64/mingw64/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(fruitwork src/Main.cpp src/System.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} SDL2main.lib SDL2.lib SDL2_image.lib SDL2_ttf.lib SDL2_mixer.lib)