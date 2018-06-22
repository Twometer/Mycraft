//
// Created by twome on 18/06/2018.
//
#include "ControlPad.h"


GLfloat ControlPad::normalize(GLfloat x) {
    return x * (viewport_width / viewport_height);
}

void ControlPad::drawRect(GuiRenderer *guiRenderer, GLfloat x, GLfloat y, int color) {
    guiRenderer->drawRect(x, y, CONTROL_SIZE, normalize(CONTROL_SIZE),
                        COLORDATA(color, color, color, 255));
}

void ControlPad::build(int viewport_width, int viewport_height) {
    this->viewport_width = viewport_width;
    this->viewport_height = viewport_height;
    controls.push_back(
            new CONTROL(0, -1.f + CONTROL_SIZE + 2 * CONTROL_PADDING,
                        -1.f + normalize(CONTROL_PADDING)));
    controls.push_back(
            new CONTROL(1, -1.f + CONTROL_SIZE + 2 * CONTROL_PADDING,
                        -1.f + normalize(2 * CONTROL_PADDING + CONTROL_SIZE)));
    controls.push_back(
            new CONTROL(2, -1.f + CONTROL_SIZE + 2 * CONTROL_PADDING,
                        -1.f + normalize(3 * CONTROL_PADDING + 2 * CONTROL_SIZE)));
    controls.push_back(
            new CONTROL(3, -1.f + CONTROL_PADDING,
                        -1.f + normalize(2 * CONTROL_PADDING + CONTROL_SIZE)));
    controls.push_back(
            new CONTROL(4, -1.f + 2 * CONTROL_SIZE + 3 * CONTROL_PADDING,
                        -1.f + normalize(2 * CONTROL_PADDING + CONTROL_SIZE)));
}

void ControlPad::render(GuiRenderer *guiRenderer) {
    for (unsigned long i = 0; i < controls.size(); i++) {
        CONTROL ctrl = *controls.at(i);
        drawRect(guiRenderer, ctrl.x, ctrl.y, ctrl.color);
    }
}

void ControlPad::handleTouch(bool down, float x, float y) {
    if (!down) {
        for (unsigned long i = 0; i < controls.size(); i++) {
            controls.at(i)->color = 255;
        }
        pressedKey = -1;
        return;
    }
    GLfloat glX = (x - viewport_width / 2.f) / (viewport_width / 2.f);
    GLfloat glY = -(y - viewport_height / 2.f) / (viewport_height / 2.f);
    for (unsigned long i = 0; i < controls.size(); i++) {
        CONTROL *ctrlPtr = controls.at(i);
        CONTROL ctrl = *ctrlPtr;
        if (glX >= ctrl.x && glY >= ctrl.y && glX <= ctrl.x + CONTROL_SIZE &&
            glY <= ctrl.y + CONTROL_SIZE) {
            ctrlPtr->color = 0;
            pressedKey = ctrl.identifier;
        } else {
            ctrlPtr->color = 255;
        }
    }
}



