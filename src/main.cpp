
// http://www.glfw.org/docs/latest/quick.html

#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>

#include <iostream>

// ----------------------------------------------------------------
void exit_and_teardown(std::string msg, long exit_status=EXIT_FAILURE) {
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(exit_status);
}

// ----------------------------------------------------------------
void error_callback(int error, const char* description) {
    std::cerr << description << std::endl;
}

// ----------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

// ----------------------------------------------------------------
void render_frame(void* arg)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(arg);
    // You can also set a framebuffer size callback using glfwSetFramebufferSizeCallback
    // and call glViewport from there.
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

float ratio = width / static_cast<float>(height);
glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glRotatef(static_cast<float>(glfwGetTime()) * 50.0f, 0.0f, 0.0f, 1.0f);

glBegin(GL_TRIANGLES);
glColor3f(  1.0f,  0.0f, 0.0f);
glVertex3f(-0.6f, -0.4f, 0.0f);
glColor3f(  0.0f,  1.0f, 0.0f);
glVertex3f( 0.6f, -0.4f, 0.0f);
glColor3f(  0.0f,  0.0f, 1.0f);
glVertex3f( 0.0f,  0.6f, 0.0f);
glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
}


int main()
{
    //
    // Setup error callback
    //
    glfwSetErrorCallback(error_callback);


    //
    // Initialize GLFW3
    //
    if (!glfwInit()) {
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


    //
    // Create window
    //
    GLFWwindow* window = glfwCreateWindow(640, 480, "Spear", NULL, NULL);
    if (!window) {
        exit_and_teardown("Could not create window.");
    } else {
        std::cout << "glfwCreateWindow success!" << std::endl;
    }

    // Set this window as the current context
    glfwMakeContextCurrent(window);


    //
    // Other settings
    //
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetKeyCallback(window, key_callback);


    //
    // Do something in the window
    //
    emscripten_set_main_loop_arg(render_frame, window, 0, 0);
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

// #include <stdio.h>
// #include <assert.h>
// #include <string.h>

// static void errorcb(int error, const char *msg) { (void)error; (void)msg; }
// static void monitcb(GLFWmonitor *monitor, int event) { assert(monitor != NULL); (void)event; }
// static void wposicb(GLFWwindow *window, int x, int y) { assert(window != NULL); (void)x; (void)y; }
// static void wsizecb(GLFWwindow *window, int w, int h) { assert(window != NULL); (void)w; (void)h; }
// static void wcloscb(GLFWwindow *window) { assert(window != NULL); }
// static void wrfrscb(GLFWwindow *window) { assert(window != NULL); }
// static void wfocucb(GLFWwindow *window, int focused) { assert(window != NULL); (void)focused; }
// static void wiconcb(GLFWwindow *window, int iconified) { assert(window != NULL); (void)iconified; }
// static void wfsizcb(GLFWwindow *window, int w, int h) { assert(window != NULL); (void)w; (void)h; }
// static void wkeypcb(GLFWwindow *window, int key, int scancode, int action, int mods) {
//     assert(window != NULL); (void)key; (void)scancode; (void)action; (void)mods;
// }
// static void wcharcb(GLFWwindow *window, unsigned int cp) { assert(window != NULL); (void)cp; }
// static void wmbutcb(GLFWwindow *window, int button, int action, int mods) {
//     assert(window != NULL); (void)button; (void)action; (void)mods;
// }
// static void wcurpcb(GLFWwindow *window, double x, double y) { assert(window != NULL); (void)x; (void)y; }
// static void wcurecb(GLFWwindow *window, int entered) { assert(window != NULL); (void)entered; }
// static void wscrocb(GLFWwindow *window, double x, double y) { assert(window != NULL); (void)x; (void)y; }

// int main()
// {
//     GLFWwindow *window;
//     char *userptr = "userptr";

//     glfwSetErrorCallback(errorcb);
//     assert(glfwInit() == GL_TRUE);
//     assert(!strcmp(glfwGetVersionString(), "3.0.0 JS WebGL Emscripten"));

//     {
//         int major, minor, rev;
//         glfwGetVersion(&major, &minor, &rev);
//         assert(major == 3);
//         assert(minor == 0);
//         assert(rev == 0);
//     }

//     {
//         int count, x, y, w, h;
//         GLFWmonitor **monitors = glfwGetMonitors(&count);
//         assert(count == 1);
//         for (int i = 0; i < count; ++i) {
//             assert(monitors[i] != NULL);
//         }

//         assert(glfwGetPrimaryMonitor() != NULL);
//         glfwGetMonitorPos(monitors[0], &x, &y);
//         glfwGetMonitorPhysicalSize(monitors[0], &w, &h);
//         assert(glfwGetMonitorName(monitors[0]) != NULL);
//         glfwSetMonitorCallback(monitcb);

//         // XXX: not implemented
//         // assert(glfwGetVideoModes(monitors[0], &count) != NULL);
//         // assert(glfwGetVideoMode(monitors[0]) != NULL);
//         // glfwSetGamma(monitors[0], 1.0f);
//         // assert(glfwGetGammaRamp(monitors[0]) != NULL);
//         // glfwSetGammaRamp(monitors[0], ramp);
//     }

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
