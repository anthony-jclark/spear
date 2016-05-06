

#include "scene/scene.h"

void draw(void* arg) {
    auto s = static_cast<scene*>(arg);
    s->render();
}


int main()
{
    scene test_scene;

    // Do something in the window
    emscripten_set_main_loop_arg(draw, &test_scene, 0, true);
    glfwSwapInterval(1);
}
