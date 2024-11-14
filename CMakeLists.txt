cmake_minimum_required(VERSION 3.21.1)

# Set the project name
project(2048-game)

project(2048-game VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/utils)

add_executable(game
	src/main.cpp)

target_link_libraries(game PRIVATE LibUtils)

target_include_directories(game PUBLIC
	"${PROJECT_BINARY_DIR}")