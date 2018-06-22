//
// Created by twome on 15/06/2018.
//

#include "GuiRenderer.h"

GuiRenderer::GuiRenderer(int dimen) {
    this->dimen = dimen;
}

GuiRenderer::~GuiRenderer() {
    vertices.clear();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertexBuffer);
    if (hasColor) glDeleteBuffers(1, &colorBuffer);
    if (hasTexture) glDeleteBuffers(1, &textureBuffer);
}

void GuiRenderer::vertex3(GLfloat x, GLfloat y, GLfloat z) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void GuiRenderer::vertex2(GLfloat x, GLfloat y) {
    vertices.push_back(x);
    vertices.push_back(y);
}

void GuiRenderer::texture2(GLfloat x, GLfloat y) {
    texVertices.push_back(x);
    texVertices.push_back(y);
    hasTexture = true;
}


void GuiRenderer::color(int r, int g, int b, int a) {
    colors.push_back((GLfloat) r / 255.0f);
    colors.push_back((GLfloat) g / 255.0f);
    colors.push_back((GLfloat) b / 255.0f);
    colors.push_back((GLfloat) a / 255.0f);
    hasColor = true;
}

void GuiRenderer::drawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, COLORDATA c) {
    color(c.r, c.g, c.b, c.a);
    vertex2(x, y);

    color(c.r, c.g, c.b, c.a);
    vertex2(x, y + h);

    color(c.r, c.g, c.b, c.a);
    vertex2(x + w, y);

    color(c.r, c.g, c.b, c.a);
    vertex2(x + w, y);

    color(c.r, c.g, c.b, c.a);
    vertex2(x, y + h);

    color(c.r, c.g, c.b, c.a);
    vertex2(x + w, y + h);
}

void
GuiRenderer::drawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, COLORDATA c, TEXDATA texdata) {
    drawRect(x, y, w, h, c);
    texture2(texdata.u0, texdata.v1);
    texture2(texdata.u0, texdata.v0);
    texture2(texdata.u1, texdata.v1);
    texture2(texdata.u1, texdata.v1);
    texture2(texdata.u0, texdata.v0);
    texture2(texdata.u1, texdata.v0);
}

void GuiRenderer::build() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices.front(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    if (hasColor) {
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), &colors.front(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (hasTexture) {
        glGenBuffers(1, &textureBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texVertices.size(), &texVertices.front(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    glBindVertexArray(0);
}

void GuiRenderer::render() {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    if (hasColor) glEnableVertexAttribArray(1);
    if (hasTexture) glEnableVertexAttribArray(2);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size() / dimen));

    if (hasTexture) glDisableVertexAttribArray(2);
    if (hasColor) glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindVertexArray(0);
}

void GuiRenderer::buildAndRender() {
    build();
    render();
}

