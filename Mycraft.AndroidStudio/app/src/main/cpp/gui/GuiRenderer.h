//
// Created by twome on 15/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_VBOBUILDER_H
#define MYCRAFT_ANDROIDSTUDIO_VBOBUILDER_H


#include <GLES3/gl3.h>
#include <vector>
#include "../glm/vec2.hpp"

struct COLORDATA {
    int r;
    int g;
    int b;
    int a;

    COLORDATA() {
        this->r = 255;
        this->g = 255;
        this->b = 255;
        this->a = 255;
    }

    COLORDATA(int r, int g, int b, int a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

struct TEXDATA {
    float u0;
    float v0;
    float u1;
    float v1;

    TEXDATA() {
        u0 = 0;
        v0 = 0;
        u1 = 1;
        v1 = 1;
    }

    TEXDATA(float u0, float v0, float u1, float v1) {
        this->u0 = u0;
        this->v0 = v0;
        this->u1 = u1;
        this->v1 = v1;
    }
};

class GuiRenderer {

private:
    GLuint vao = 0;
    int dimen = 0;
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> texVertices;
    GLuint vertexBuffer = 0;
    GLuint textureBuffer = 0;
    GLuint colorBuffer = 0;

    bool hasColor;
    bool hasTexture;
public:
    GuiRenderer(int dimen);

    ~GuiRenderer();

    void vertex3(GLfloat x, GLfloat y, GLfloat z);

    void vertex2(GLfloat x, GLfloat y);

    void texture2(GLfloat u, GLfloat v);

    void drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, COLORDATA color,
                  TEXDATA useTextures);

    void drawRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, COLORDATA color);

    void drawRectNormalized(GLfloat x, GLfloat y, GLfloat width, GLfloat height, COLORDATA color, glm::vec2 viewport);

    void color(int r, int g, int b, int a);

    void build();

    void render();

    void buildAndRender();
};


#endif //MYCRAFT_ANDROIDSTUDIO_VBOBUILDER_H
