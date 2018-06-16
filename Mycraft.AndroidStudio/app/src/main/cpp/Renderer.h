//
// Created by twome on 16/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_RENDERER_H
#define MYCRAFT_ANDROIDSTUDIO_RENDERER_H


#include "Loader.h"

class Renderer {
public:
    void initialize(Loader loader);
    void resize(int width, int height);
    void drawFrame();
};


#endif //MYCRAFT_ANDROIDSTUDIO_RENDERER_H
