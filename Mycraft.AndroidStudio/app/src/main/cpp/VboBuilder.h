//
// Created by twome on 15/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_VBOBUILDER_H
#define MYCRAFT_ANDROIDSTUDIO_VBOBUILDER_H


#include <GLES3/gl3.h>
#include <vector>

struct COLORDATA {
    int r;
    int g;
    int b;
    int a;

    COLORDATA() {

    }

    COLORDATA(int r, int g, int b, int a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

class VboBuilder {

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
    VboBuilder(int dimen);

    ~VboBuilder();

    void vertex3(int x, int y, int z);

    void vertex2(int x, int y);

    void texture2(int u, int v);

    void drawRect(int x, int y, int width, int height, COLORDATA color, bool useTextures);

    void drawRect(int x, int y, int width, int height, COLORDATA color);

    void color(int r, int g, int b, int a);

    void build();

    void render();

    void buildAndRender();
};


#endif //MYCRAFT_ANDROIDSTUDIO_VBOBUILDER_H
