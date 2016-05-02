# spear

Sandbox for playing with Emscripten and WebGL

## Third Party

### GLFW3

I have decided to use GLFW for windowing and handling events as that is the library with which I am most familiar. I also did not want to use the GL emulation mode that Emscripten provides.

Using GLFW3 with GLES2 requires a couple of changes to most basic examples that are provided in the Emscripten tests.

1. The flag `-s USE_GLFW=3` must be set during the **linking** process.
2. The definition `#GLFW_INCLUDE_ES3` needs to be provided to tell GLFW3 to include the appropriate version of OpenGL.
