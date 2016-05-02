
include (CXXFlags)
add_executable (testbin main.cpp)

set (CMAKE_EXECUTABLE_SUFFIX ".html")

set (USE_GLFW3 "-s USE_GLFW=3")
list (APPEND CMAKE_EXE_LINKER_FLAGS "${USE_GLFW3}")

