add_library(LibUtils
	row_merge.cpp
	row_merge.hpp
)

target_include_directories(LibUtils
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)