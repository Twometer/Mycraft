//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_BLOCK_H
#define MYCRAFT_ANDROIDSTUDIO_BLOCK_H

#include "Texture.h"

enum RendererType {
    Fluid,
    Transparent,
    Plant,
    Solid
};

class Block {
public:
    char id;
    RendererType rendererType;
    TEXTURE topTex;
    TEXTURE sideTex;
    TEXTURE bottomTex;

    Block(char id, TEXTURE topTex, TEXTURE sideTex, TEXTURE bottomTex, RendererType rendererType);
};
#endif //MYCRAFT_ANDROIDSTUDIO_BLOCK_H
