//
// Created by twome on 26/12/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_CROSSHAIRRENDERER_H
#define MYCRAFT_ANDROIDSTUDIO_CROSSHAIRRENDERER_H


#include <GLES3/gl3.h>

class CrosshairRenderer {
private:
    GLuint vao;
    GLuint texture;
    void loadToVao();
public:
    void init();
    void render();
    CrosshairRenderer(GLuint texture);
};


#endif //MYCRAFT_ANDROIDSTUDIO_CROSSHAIRRENDERER_H
