add_executable(utils_test
	main.cpp)

target_link_libraries(utils_test
	PRIVATE LibCore
	PRIVATE LibUtils)
