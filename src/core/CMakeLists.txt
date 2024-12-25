# Link libraries if any (example)
# target_link_libraries(2048-game some_library)
# Create a library target for the header files
add_library(LibCore INTERFACE)

# Specify the include directories for the library
target_include_directories(LibCore INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
