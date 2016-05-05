
##
## Add the executable target
##
include (CXXFlags)
file (GLOB_RECURSE test_SRCS *.cpp *.h)
set (test_BIN ${PROJECT_NAME}-UnitTests)
add_executable (${test_BIN} ${test_SRCS})
# set (CMAKE_EXECUTABLE_SUFFIX ".html")



# ##
# ## Add definition for compiling the test version of code
# ##
# target_compile_definitions (${test_BIN} PUBLIC ${TEST})


##
## Link the target with support files (header only libraries).
##
target_include_directories (
    ${test_BIN} SYSTEM PUBLIC ${SUPPORT_PATH}/Catch/single_include/
)
target_include_directories (${test_BIN} SYSTEM PUBLIC ${SRC_PATH})


##
## Link the target with libraries
##
target_link_libraries (${test_BIN}
    matrix4
    vector3
    linalg
)

