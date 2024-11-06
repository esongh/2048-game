cmake_minimum_required(VERSION 3.21.1)

# Set the project name
project(2048-game)

project(2048-game VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(game src/main.cpp)