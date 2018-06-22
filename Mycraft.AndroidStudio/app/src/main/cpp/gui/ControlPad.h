//
// Created by twome on 18/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_CONTROLPAD_H
#define MYCRAFT_ANDROIDSTUDIO_CONTROLPAD_H

#define CONTROL_PADDING 0.05f
#define CONTROL_SIZE 0.15f

#define CONTROL_BACKWARD 0
#define CONTROL_JUMP 1
#define CONTROL_FORWARD 2
#define CONTROL_LEFT 3
#define CONTROL_RIGHT 4

#include <vector>
#include <GLES3/gl3.h>
#include "GuiRenderer.h"

struct CONTROL {
    int identifier;
    GLfloat x;
    GLfloat y;

    int color = 255;

    CONTROL(int identifier, GLfloat x, GLfloat y) {
        this->identifier = identifier;
        this->x = x;
        this->y = y;
    }
};

class ControlPad {

private:
    int viewport_width;

    int viewport_height;

    std::vector<CONTROL*> controls;

    void drawRect(GuiRenderer *guiRenderer, GLfloat x, GLfloat y, int color);

    GLfloat normalize(GLfloat x);

public:
    int pressedKey = -1;

    void build(int viewport_width, int viewport_height);

    void handleTouch(bool down, float x, float y);

    void render(GuiRenderer *guiRenderer);
};


#endif //MYCRAFT_ANDROIDSTUDIO_CONTROLPAD_H
