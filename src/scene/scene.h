
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../render/renderer.h"

class scene
{
    renderer m_renderer;
public:
    // scene();
    void render() {
        m_renderer.render_frame();
    }
};

#endif
