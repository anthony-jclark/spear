# spear

Sandbox for playing with Emscripten and WebGL

## Rendering

At least to start, I will be using a 4x4 matrix (matrix4) to describe the transform of each mesh. I think it will make working with OGL easier. It may be worth changing this to a quaternion and position vector later on.

## General

It turns out that inline functions is not necessarily the best thing to do when compiling C++ to Javascript. See [outlining](https://kripken.github.io/emscripten-site/docs/optimizing/Optimizing-Code.html#optimizing-code-outlining) for more information.

## Third Party

### GLFW3

I have decided to use GLFW for windowing and handling events as that is the library with which I am most familiar. I also did not want to use the GL emulation mode that Emscripten provides.

Using GLFW3 with GLES2 requires a couple of changes to most basic examples that are provided in the Emscripten tests.

1. The flag `-s USE_GLFW=3` must be set during the **linking** process.
2. The definition `#GLFW_INCLUDE_ES3` needs to be provided to tell GLFW3 to include the appropriate version of OpenGL.

### Catch

I am using Catch for unit testing. To run all tests for a specific tag use the following command (where vector3 is a tag):

```bash
node spear-UnitTests.js [vector3]
```

