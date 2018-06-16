//
// Created by twome on 15/06/2018.
//

#include "VboBuilder.h"
#include <android/log.h>
#define  LOG_TAG    "MyCraft_Native"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

VboBuilder::VboBuilder(int dimen)
{
    this->dimen = dimen;
}

VboBuilder::~VboBuilder()
{
    vertices.clear();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertexBuffer);
    if (hasColor) glDeleteBuffers(1, &colorBuffer);
    if (hasTexture) glDeleteBuffers(1, &textureBuffer);
}

void VboBuilder::vertex3(GLfloat x, GLfloat y, GLfloat z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void VboBuilder::vertex2(GLfloat x, GLfloat y)
{
    vertices.push_back(x);
    vertices.push_back(y);
}

void VboBuilder::texture2(GLfloat x, GLfloat y)
{
    texVertices.push_back(x);
    texVertices.push_back(y);
    hasTexture = true;
}


void VboBuilder::color(int r, int g, int b, int a)
{
    colors.push_back((GLfloat)r / 255.0f);
    colors.push_back((GLfloat)g / 255.0f);
    colors.push_back((GLfloat)b / 255.0f);
    colors.push_back((GLfloat)a / 255.0f);
    hasColor = true;
}
void VboBuilder::drawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, COLORDATA c) {
    drawRect(x, y, w, h, c, false);
}
void VboBuilder::drawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, COLORDATA c, bool useTextures)
{
    if(useTextures) texture2(0, 0);
    color(c.r, c.g, c.b, c.a);
    vertex2(x, y + h);

    if (useTextures) texture2(0, 1);
    color(c.r, c.g, c.b, c.a);
    vertex2(x, y);

    if (useTextures) texture2(1, 0);
    color(c.r, c.g, c.b, c.a);
    vertex2(x + w, y + h);

    if (useTextures) texture2(1, 1);
    color(c.r, c.g, c.b, c.a);
    vertex2(x + w, y);
}

void VboBuilder::build()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    if (hasColor) {
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), &colors.front(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (hasTexture) {
        glGenBuffers(1, &textureBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texVertices.size(), &texVertices.front(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    glBindVertexArray(0);
}

void VboBuilder::render()
{
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    if (hasColor) glEnableVertexAttribArray(1);
    if (hasTexture) glEnableVertexAttribArray(2);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / dimen);

    if (hasTexture) glDisableVertexAttribArray(2);
    if (hasColor) glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindVertexArray(0);
}

void VboBuilder::buildAndRender() {
    build();
    render();
}