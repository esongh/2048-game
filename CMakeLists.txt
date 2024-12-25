cmake_minimum_required(VERSION 3.21.1)

# Set the project name
project(2048-game)

project(2048-game VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
	GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
	GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

add_subdirectory(src/core)
add_subdirectory(src/ui)
add_subdirectory(src/utils)

add_executable(game
	src/game.cpp
	src/game.hpp
	src/main.cpp)

target_link_libraries(game
	PRIVATE LibUI
	PRIVATE LibUtils
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)

target_include_directories(game PUBLIC
	"${PROJECT_BINARY_DIR}")
	
add_subdirectory(test)
