
#include "renderer.h"

#include <iostream>
#include <array>



// ----------------------------------------------------------------
void exit_and_teardown(std::string msg, long exit_status) {
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(exit_status);
}

// ----------------------------------------------------------------
void error_callback(int error, const char* description) {
    std::cerr << description << " (error : " << error << ")" << std::endl;
}

// ----------------------------------------------------------------
// http://www.glfw.org/docs/3.0/group__window.html#ga3d2fc6026e690ab31a13f78bc9fd3651
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    UNUSED(window);
}


GLuint LoadShader(GLenum type, const char* shaderSrc)
{
    // Create the shader object
    GLuint shader = glCreateShader(type);
    if (shader == GL_FALSE) {
        exit_and_teardown("ERROR: Could not create shader.");
    }

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled == GL_FALSE) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            std::vector<GLchar> infoLog(static_cast<size_t>(infoLen));
            glGetShaderInfoLog(shader, infoLen, nullptr, &infoLog[0]);
            exit_and_teardown(std::string("ERROR: Could not compile shader: ") + &infoLog[0]);
        }

        glDeleteShader(shader);
        return GL_FALSE;
    }

    return shader;
}



renderer::renderer(GLint xsize, GLint ysize)
    : m_xsize(xsize)
    , m_ysize(ysize)
{
    // Setup error callback
    glfwSetErrorCallback(error_callback);

    // Initialize GLFW3
    if (glfwInit() == GL_FALSE) {
        std::cout << "Could not init glfw." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create window
    m_window = glfwCreateWindow(m_xsize, m_ysize, WINDOW_NAME.c_str(), nullptr, nullptr);
    if (m_window == nullptr) {
        exit_and_teardown("ERROR: Could not create window.");
    }

    // Set this window as the current context
    glfwMakeContextCurrent(m_window);

    // OpenGL settings
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClearDepthf(1);
    glClearStencil(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glClearColor(1, 1, 1, 1);

    // Callbacks
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Create shader program
    {
        std::string vertexShaderStr {
            "attribute vec4 vPosition;                              \n"
            "void main()                                            \n"
            "{                                                      \n"
            "   gl_Position = vPosition;                            \n"
            "}                                                      \n"
        };

        std::string fragmentShaderStr {
            "precision mediump float;                               \n"
            "void main()                                            \n"
            "{                                                      \n"
            "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );          \n"
            "}                                                      \n"
        };

        // Load the vertex/fragment shaders
        GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderStr.c_str());
        GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderStr.c_str());

        // Create the program object
        m_programs.push_back(glCreateProgram());
        if (m_programs.back() == GL_FALSE) {
            exit_and_teardown("ERROR: Could not create shader program.");
        }
        glAttachShader(m_programs.back(), vertexShader);
        glAttachShader(m_programs.back(), fragmentShader);

        // Bind vPosition to attribute 0
        glBindAttribLocation(m_programs.back(), 0, "vPosition");

        // Link the program
        glLinkProgram(m_programs.back());

        // Check the link status
        GLint linked;
        glGetProgramiv(m_programs.back(), GL_LINK_STATUS, &linked);

        if (linked == GL_FALSE) {
            GLint infoLen = 0;
            glGetProgramiv(m_programs.back(), GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1) {
                std::vector<GLchar> infoLog(static_cast<size_t>(infoLen));
                glGetProgramInfoLog(m_programs.back(), infoLen, nullptr, &infoLog[0]);
                exit_and_teardown(std::string("ERROR: Could not link program: ") + &infoLog[0]);
            }

            glDeleteProgram(m_programs.back());
            // return GL_FALSE;
        }
    }
}

// ----------------------------------------------------------------
void renderer::render_frame()
{
    // Create an array of vertices
    const GLint NUM_VERTS = 9;
    std::array<GLfloat, NUM_VERTS> vVertices {{
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    }};

    // No clientside arrays, so do this in a webgl-friendly manner
    GLuint vertexPosObject;
    glGenBuffers(1, &vertexPosObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
    glBufferData(GL_ARRAY_BUFFER, NUM_VERTS * sizeof(GLfloat), &vVertices[0], GL_STATIC_DRAW);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(m_programs[0]);

    // Load the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    // Draw the vertices to the buffer
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap the buffered frame to the front
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}