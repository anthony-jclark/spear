
include (CXXFlags)
add_executable (testbin main.cpp)

set (CMAKE_EXECUTABLE_SUFFIX ".html")

set (USE_GLFW3 "-s USE_GLFW=3")
# set (USE_GL_EMULATION "-s LEGACY_GL_EMULATION=1")
# set (GEN_HTML "-o index.html")
list (APPEND CMAKE_EXE_LINKER_FLAGS "${USE_GLFW3}")# ${USE_GL_EMULATION} ${GEN_HTML}")
