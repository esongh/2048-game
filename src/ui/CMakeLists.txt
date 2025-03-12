set(SOURCE
	animation.cpp
	animation.hpp
	theme.hpp
	tile.cpp
	tile.hpp
)

list(APPEND SOURCE
	${lodepng_SOURCE_DIR}/lodepng.cpp
)
add_library(LibUI ${SOURCE})

target_include_directories(LibUI PUBLIC ${lodepng_SOURCE_DIR})

target_include_directories(LibUI
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LibUI
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)
