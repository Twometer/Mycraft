//
// Created by twome on 17/06/2018.
//

#include "SectionRenderer.h"
#include "Vertices.h"
#include "../block/BlockRegistry.h"
#include "../Renderer.h"

#define TEXTURE_OFFSET 0.03125f

SectionRenderer::SectionRenderer(Section *section) {
    this->section = section;
    this->vertices = new GLfloat[120000]; // Three entries per vertex
    this->verticesAlloc = 0;
    this->colors = new GLfloat[120000]; // Three entries per vertex
    this->colorsAlloc = 0;
    this->textureCoords = new GLfloat[90000]; // Two entries per vertex
    this->textureCoordsAlloc = 0;
}

void SectionRenderer::buildData() {
    Section sec = *section;
    int xo = sec.x << 4;
    int yo = sec.idx << 4;
    int zo = sec.z << 4;

    int absX;
    int absY;
    int absZ;

    for (int x = 0; x < 16; x++) {
        absX = x + xo;
        for (int y = 0; y < 16; y++) {
            absY = y + yo;
            for (int z = 0; z < 16; z++) {
                absZ = z + zo;
                unsigned char blockId = sec.getBlock(x, y, z);
                if (blockId != 0) {
                    Block block = *BlockRegistry::getBlock(blockId);
                    int texX = block.sideTex.x;
                    int texY = block.sideTex.y;
                    if (block.rendererType == Plant) {
                        putGeometry(plantvertices_a, tplantvertices_a, absX, absY, absZ, texX, texY,
                                    1.0f, vertices, colors, textureCoords, &verticesAlloc,
                                    &textureCoordsAlloc, &colorsAlloc);
                        putGeometry(plantvertices_b, tplantvertices_b, absX, absY, absZ, texX, texY,
                                    1.0f, vertices, colors, textureCoords, &verticesAlloc,
                                    &textureCoordsAlloc, &colorsAlloc);
                        putGeometry(plantvertices_c, tplantvertices_c, absX, absY, absZ, texX, texY,
                                    1.0f, vertices, colors, textureCoords, &verticesAlloc,
                                    &textureCoordsAlloc, &colorsAlloc);
                        putGeometry(plantvertices_d, tplantvertices_d, absX, absY, absZ, texX, texY,
                                    1.0f, vertices, colors, textureCoords, &verticesAlloc,
                                    &textureCoordsAlloc, &colorsAlloc);
                    } else {
                        if (getBlock(x + 1, y, z, absX + 1, absY, absZ) == 0)
                            putGeometry(vertices_positive_x, tvertices_positive_x, absX,
                                        absY, absZ, texX, texY, 0.75f, vertices, colors,
                                        textureCoords, &verticesAlloc, &textureCoordsAlloc,
                                        &colorsAlloc);
                        if (getBlock(x - 1, y, z, absX - 1, absY, absZ) == 0)
                            putGeometry(vertices_negative_x, tvertices_negative_x, absX,
                                        absY, absZ, texX, texY, 0.75f, vertices, colors,
                                        textureCoords, &verticesAlloc, &textureCoordsAlloc,
                                        &colorsAlloc);

                        if (getBlock(x, y, z + 1, absX, absY, absZ + 1) == 0)
                            putGeometry(vertices_positive_z, tvertices_positive_z, absX,
                                        absY, absZ, texX, texY, 0.65f, vertices, colors,
                                        textureCoords, &verticesAlloc, &textureCoordsAlloc,
                                        &colorsAlloc);
                        if (getBlock(x, y, z - 1, absX, absY, absZ - 1) == 0)
                            putGeometry(vertices_negative_z, tvertices_negative_z, absX,
                                        absY, absZ, texX, texY, 0.65f, vertices, colors,
                                        textureCoords, &verticesAlloc, &textureCoordsAlloc,
                                        &colorsAlloc);

                        texX = block.topTex.x;
                        texY = block.topTex.y;
                        if (getBlock(x, y + 1, z, absX, absY + 1, absZ) == 0)
                            putGeometry(vertices_positive_y, tvertices_positive_y, absX,
                                        absY, absZ, texX, texY, 1.00f, vertices, colors,
                                        textureCoords, &verticesAlloc, &textureCoordsAlloc,
                                        &colorsAlloc);

                        texX = block.bottomTex.x;
                        texY = block.bottomTex.y;
                        if (getBlock(x, y - 1, z, absX, absY - 1, absZ) == 0)
                            putGeometry(vertices_negative_y, tvertices_negative_y, absX,
                                        absY, absZ, texX, texY, 0.60f, vertices, colors,
                                        textureCoords, &verticesAlloc, &textureCoordsAlloc,
                                        &colorsAlloc);
                    }
                }
            }
        }
    }

    section->setState(STATE_SHOULD_UPLOAD);
}

void SectionRenderer::uploadData() {
    int sz = sizeof(GLfloat);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticesAlloc * sz, vertices, GL_STATIC_DRAW);
    buffers.vertexBuffer = vertexBuffer;

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colorsAlloc * sz, colors, GL_STATIC_DRAW);
    buffers.colorBuffer = colorBuffer;

    GLuint textureBuffer;
    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, textureCoordsAlloc * sz, textureCoords, GL_STATIC_DRAW);
    buffers.textureBuffer = textureBuffer;

    delete[] vertices;
    delete[] colors;
    delete[] textureCoords;
}

void SectionRenderer::render() {
    glBindBuffer(GL_ARRAY_BUFFER, buffers.vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers.colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers.textureBuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glDrawArrays(GL_TRIANGLES, 0, verticesAlloc / 3);
}

void
SectionRenderer::putGeometry(const GLfloat *vertices, const GLfloat *textureCoords, int x, int y,
                             int z, int texX, int texY, GLfloat color, GLfloat *verticesTarget,
                             GLfloat *colorTarget, GLfloat *textureTarget, int *verticesCounter,
                             int *textureCounter, int *colorCounter) {

    for (int i = 0; i < 18; i += 3) {
        int vc = *verticesCounter;
        int cc = *colorCounter;
        verticesTarget[vc] = vertices[i] + x;
        verticesTarget[vc + 1] = vertices[i + 1] + y;
        verticesTarget[vc + 2] = vertices[i + 2] + z;
        (*verticesCounter) += 3;
        colorTarget[cc] = color;
        colorTarget[cc + 1] = color;
        colorTarget[cc + 2] = color;
        (*colorCounter) += 3;
    }

    for (int i = 0; i < 12; i += 2) {
        int tc = *textureCounter;
        textureTarget[tc] = textureCoords[i] * TEXTURE_OFFSET + texX * TEXTURE_OFFSET;
        textureTarget[tc + 1] = textureCoords[i + 1] * TEXTURE_OFFSET + texY * TEXTURE_OFFSET;
        (*textureCounter) += 2;
    }

}

unsigned char SectionRenderer::getBlock(int x, int y, int z, int absX, int absY, int absZ) {
    if (x < 0 || y < 0 || z < 0 || x > 15 || y > 15 || z > 15)
        return Renderer::getWorld()->getBlock(absX, absY, absZ);
    else return section->getBlock(x, y, z);
}
