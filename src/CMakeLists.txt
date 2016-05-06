
add_subdirectory (linalg)
add_subdirectory (render)
add_subdirectory (scene)

include (CXXFlags)
add_executable (spear main.cpp)

set (CMAKE_EXECUTABLE_SUFFIX ".html")
set (USE_GLFW3 "-s USE_GLFW=3")
list (APPEND CMAKE_EXE_LINKER_FLAGS "${USE_GLFW3}")

target_link_libraries (spear renderer)
