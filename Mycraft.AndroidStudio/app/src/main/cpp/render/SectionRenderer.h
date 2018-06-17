//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_SECTIONRENDERER_H
#define MYCRAFT_ANDROIDSTUDIO_SECTIONRENDERER_H


#include <GLES3/gl3.h>
#include "../world/Section.h"

struct Buffers {
    GLuint vertexBuffer = 0;
    GLuint colorBuffer = 0;
    GLuint textureBuffer = 0;
};

class Section;
class SectionRenderer {

private:
    Section *section;

    GLfloat *vertices;
    int verticesAlloc;

    GLfloat *colors;
    int colorsAlloc;

    GLfloat *textureCoords;
    int textureCoordsAlloc;

    Buffers buffers;

    void putGeometry(const GLfloat *vertices, const GLfloat *textureCoords, int x, int y, int z,
                     int texX, int texY, GLfloat color, GLfloat *verticesTarget,
                     GLfloat *colorTarget, GLfloat *textureTarget, int *verticesCounter,
                     int *textureCounter, int *colorCounter);

    unsigned char getBlock(int x, int y, int z, int absX, int absY, int absZ);

public:
    SectionRenderer(Section *section);

    void buildData();

    void uploadData();

    void render();

};


#endif //MYCRAFT_ANDROIDSTUDIO_SECTIONRENDERER_H
