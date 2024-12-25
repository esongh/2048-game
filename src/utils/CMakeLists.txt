add_library(LibUtils
	row_merge.cpp
	row_merge.hpp
)

target_include_directories(LibUtils
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(LibUtils
	PRIVATE LibCore
)
