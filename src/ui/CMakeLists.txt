add_library(LibUI
	animation.cpp
	animation.hpp
	theme.hpp
)

target_include_directories(LibUI
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LibUI
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)
