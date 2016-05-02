
// http://www.glfw.org/docs/latest/quick.html

#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>

#include <iostream>
#include <vector>
#include <array>
#include <string>

#define UNUSED(x) (void)(sizeof((x), 0))

//
// Struct containing rendering info
//
struct RenderInfo
{
    GLFWwindow* window;
    GLuint program;
};

// ----------------------------------------------------------------
void exit_and_teardown(std::string msg, long exit_status=EXIT_FAILURE) {
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(exit_status);
}

// ----------------------------------------------------------------
void error_callback(int error, const char* description) {
    std::cerr << description << " (error : " << error << ")" << std::endl;
}

// ----------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    UNUSED(scancode);
    UNUSED(mods);
}

// ----------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    UNUSED(window);
}

// ----------------------------------------------------------------
void render_frame(void* arg)
{
    // Cast the input argument to a render info object
    auto render_info = static_cast<RenderInfo*>(arg);

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
    glUseProgram(render_info->program);

    // Load the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);

    // Draw the vertices to the buffer
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap the buffered frame to the front
    glfwSwapBuffers(render_info->window);
    glfwPollEvents();
}



GLFWwindow* init_context()
{
    // Setup error callback
    glfwSetErrorCallback(error_callback);

    // Initialize GLFW3
    if (glfwInit() == GL_FALSE) {
        std::cout << "Could not init glfw." << std::endl;
        exit(EXIT_FAILURE);
    } else {
        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);
        std::cout << "glfwInit success!"
                  << "\n  " << glfwGetVersionString()
                  << "\n  Version : " <<  major << "." << minor << "." << rev
                  << std::endl;
    }

    // Create window
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    GLFWwindow* window = glfwCreateWindow(640/2, 480/2, "Spear", nullptr, nullptr);
    if (window == nullptr) {
        exit_and_teardown("ERROR: Could not create window.");
    } else {
        std::cout << "glfwCreateWindow success!" << std::endl;
    }

    // Set this window as the current context
    glfwMakeContextCurrent(window);

    // Other settings
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

GLuint LoadShader(GLenum type, const char* shaderSrc)
{
    // Create the shader object
    GLuint shader = glCreateShader(type);
    if (shader == GL_FALSE) {
        exit_and_teardown("ERROR: Could not create shader.");
    } else {
        std::cout << "glCreateShader success!" << std::endl;
    }

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled == GL_FALSE)
    {
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
    else {
        std::cout << "glCompileShader success!" << std::endl;
    }

    return shader;
}

GLuint init_shaders()
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
    GLuint programObject = glCreateProgram();
    if (programObject == GL_FALSE) {
        exit_and_teardown("ERROR: Could not create shader program.");
    } else {
        std::cout << "glCreateProgram success!" << std::endl;
    }
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");

    // Link the program
    glLinkProgram(programObject);

    // Check the link status
    GLint linked;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (linked == GL_FALSE)
    {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            std::vector<GLchar> infoLog(static_cast<size_t>(infoLen));
            glGetProgramInfoLog(programObject, infoLen, nullptr, &infoLog[0]);
            exit_and_teardown(std::string("ERROR: Could not link program: ") + &infoLog[0]);
        }

        glDeleteProgram(programObject);
        return GL_FALSE;
    }
    else {
        std::cout << "glLinkProgram success!" << std::endl;
    }

    return programObject;
}


int main()
{
    // Initialize GLFW3 and get a rendering context
    RenderInfo ri;
    ri.window = init_context();
    ri.program = init_shaders();

    // Do something in the window
    emscripten_set_main_loop_arg(render_frame, &ri, 0, true);
    glfwSwapInterval(1);

    // #ifndef NOT_BUILDING_FOR_WEB
    // #else
    // glfwSwapInterval(1);
    // while (!glfwWindowShouldClose(window)) {
    //     render_frame();
    // }
    // glfwDestroyWindow(window);
    // exit_and_teardown("Program ended normally.", EXIT_SUCCESS);
    // #endif

}


// int main()
// {

//     {
//         int x, y, w, h;
//         glfwDefaultWindowHints();
//         glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

//         window = glfwCreateWindow(640, 480, "glfw3.c", NULL, NULL);
//         assert(window != NULL);

//         glfwSetWindowPosCallback(window, wposicb);
//         glfwSetWindowSizeCallback(window, wsizecb);
//         glfwSetWindowCloseCallback(window, wcloscb);
//         glfwSetWindowRefreshCallback(window, wrfrscb);
//         glfwSetWindowFocusCallback(window, wfocucb);
//         glfwSetWindowIconifyCallback(window, wiconcb);
//         glfwSetFramebufferSizeCallback(window, wfsizcb);

//         assert(glfwWindowShouldClose(window) == 0);
//         glfwSetWindowShouldClose(window, 1);
//         assert(glfwWindowShouldClose(window) == 1);

//         glfwSetWindowTitle(window, "test");
//         glfwSetWindowTitle(window, "glfw3.c");

//         // XXX: not implemented
//         // glfwSetWindowPos(window, 1, 1);

//         glfwGetWindowPos(window, &x, &y); // stub
//         glfwGetWindowSize(window, &w, &h);
//         assert(w == 640 && h == 480);

//         glfwSetWindowSize(window, 1, 1);
//         glfwGetWindowSize(window, &w, &h);
//         assert(w == 1 && h == 1);

//         glfwSetWindowSize(window, 640, 480);
//         glfwGetFramebufferSize(window, &w, &h);

//         // XXX: not implemented
//         // glfwIconifyWindow(window);
//         // glfwRestoreWindow(window);
//         // glfwShowWindow(window);
//         // glfwHideWindow(window);

//         assert(glfwGetWindowMonitor(window) == NULL);
//         glfwDestroyWindow(window);

//         window = glfwCreateWindow(640, 480, "glfw3.c", glfwGetPrimaryMonitor(), NULL);
//         assert(window != NULL);
//         assert(glfwGetWindowMonitor(window) == glfwGetPrimaryMonitor());
//         glfwDestroyWindow(window);

//         window = glfwCreateWindow(640, 480, "glfw3.c", NULL, NULL);
//         assert(window != NULL);

//         assert(glfwGetWindowAttrib(window, GLFW_CLIENT_API) == GLFW_OPENGL_ES_API);

//         assert(glfwGetWindowUserPointer(window) == NULL);
//         glfwSetWindowUserPointer(window, userptr);
//         assert(glfwGetWindowUserPointer(window) == userptr);
//     }

//     {
//         double x, y;

//         glfwSetKeyCallback(window, wkeypcb);
//         glfwSetCharCallback(window, wcharcb);
//         glfwSetMouseButtonCallback(window, wmbutcb);
//         glfwSetCursorPosCallback(window, wcurpcb);
//         glfwSetCursorEnterCallback(window, wcurecb);
//         glfwSetScrollCallback(window, wscrocb);

//         // XXX: stub, events come immediatly
//         // glfwPollEvents();
//         // glfwWaitEvents();

//         assert(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL);

//         // XXX: not implemented
//         // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

//         glfwGetKey(window, GLFW_KEY_A);
//         glfwGetMouseButton(window, 0);
//         glfwGetCursorPos(window, &x, &y);

//         // XXX: not implemented
//         // glfwSetCursorPos(window, 0, 0);
//     }

//     {
//         // XXX: not implemented
//         // glfwJoystickPresent(joy);
//         // glfwGetJoystickAxes(joy, &count);
//         // glfwGetJoystickButtons(joy, &count);
//         // glfwGetJoystickName(joy);
//     }

//     {
//         // XXX: not implemented
//         // glfwSetClipboardString(window, "string");
//         // glfwGetClipboardString(window);
//     }

//     {
//         glfwGetTime();
//         glfwSetTime(0);
//     }

//     {
//         glfwMakeContextCurrent(window); // stub
//         assert(glfwGetCurrentContext() == window);
//         glfwSwapBuffers(window); // stub
//         glfwSwapInterval(0); // stub
//     }

//     {
//         assert(glfwExtensionSupported("nonexistant") == 0);
//         assert(glfwGetProcAddress("nonexistant") == NULL);
//     }

//     glfwTerminate();

// #ifdef REPORT_RESULT
//     int result = 1;
//     REPORT_RESULT();
// #endif
//     return 0;
// }
