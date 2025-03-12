add_executable(utils_test
	main.cpp)

target_link_libraries(utils_test
	PRIVATE LibCore
	PRIVATE LibUtils)

add_executable(ui_test
	ui_main.cpp)

target_link_libraries(ui_test
	PRIVATE LibUI
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)
