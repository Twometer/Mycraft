//
// Created by twome on 16/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_RENDERER_H
#define MYCRAFT_ANDROIDSTUDIO_RENDERER_H

#include "Loader.h"
#include "glm/vec2.hpp"

class Renderer {
public:
    void initialize(Loader loader);

    void resize(int width, int height);

    void drawFrame();

    glm::vec2 getSize();

    void rotatePlayer(float dx, float dy);
};


#endif //MYCRAFT_ANDROIDSTUDIO_RENDERER_H
