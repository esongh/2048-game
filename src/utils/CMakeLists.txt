add_library(LibUtils
	row_merge.cpp
	row_merge.hpp
)

target_link_libraries(LibUtils
	PUBLIC LibCore
)

target_include_directories(LibUtils
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
