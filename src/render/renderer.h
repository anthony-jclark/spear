
#ifndef _RENDERER_H_
#define _RENDERER_H_

#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>

#include <string>
#include <vector>

#include <iostream>

#define UNUSED(x) (void)(sizeof((x), 0))

using GLprogram = GLuint;

void exit_and_teardown(std::string msg, long exit_status=EXIT_FAILURE);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


//------------------------------------------------------------------------------
/// @brief      The renderer class is responsible for setting up OpenGL and the
/// windowing system. Then it takes meshes and renders them to the buffer.
///
class renderer
{
    const std::string WINDOW_NAME = "spear";

    GLFWwindow* m_window;
    GLint m_xsize;
    GLint m_ysize;

    std::vector<GLprogram> m_programs;

public:
    renderer(GLint xsize=640/2, GLint ysize=480/2);

    void render_frame();

};

#endif
