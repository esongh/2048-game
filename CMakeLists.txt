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

FetchContent_Declare(lodepng
	GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
	GIT_TAG master
)
FetchContent_MakeAvailable(lodepng)

add_subdirectory(src/core)
add_subdirectory(src/ui)
add_subdirectory(src/utils)

add_executable(game
	src/game_ui.cpp
	src/game_ui.hpp
	src/game.cpp
	src/game.hpp
	src/homepage.cpp
	src/homepage.hpp
	src/main.cpp)

target_link_libraries(game
	PRIVATE LibUI
	PRIVATE LibUtils
	PRIVATE LibCore
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)

target_include_directories(game PUBLIC
	"${PROJECT_SOURCE_DIR}/src/core"
	"${PROJECT_BINARY_DIR}")
	
add_subdirectory(test)

# Set the source and destination paths
set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/art_asset/texture_slim.png")
set(DESTINATION_DIR "${CMAKE_BINARY_DIR}/Debug/")

# Create the destination directory if it doesn't exist
file(MAKE_DIRECTORY ${DESTINATION_DIR})

# Copy the file to the destination directory
file(COPY ${SOURCE_FILE} DESTINATION ${DESTINATION_DIR})
