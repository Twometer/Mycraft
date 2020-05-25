//
// Created by twome on 26/12/2018.
//

#include "CrosshairRenderer.h"
void CrosshairRenderer::loadToVao() {

    GLfloat POSITIONS[] = { 0, 16, 0, 0, 16, 16, 16, 0 };
    const int AMOUNT = 8;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * AMOUNT, POSITIONS, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

CrosshairRenderer::CrosshairRenderer(GLuint texture)
{
    this->texture = texture;
}

void CrosshairRenderer::render() {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void CrosshairRenderer::init() {
    loadToVao();
}