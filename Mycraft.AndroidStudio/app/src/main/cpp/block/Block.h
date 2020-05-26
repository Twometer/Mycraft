//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_BLOCK_H
#define MYCRAFT_ANDROIDSTUDIO_BLOCK_H

#include <cstdint>
#include "Sprite.h"

enum RendererType {
    Fluid,
    Transparent,
    Plant,
    Solid
};

class Block {
public:
    uint8_t id;
    RendererType rendererType;
    Sprite topTex;
    Sprite sideTex;
    Sprite bottomTex;
    bool noClip;

    Block(uint8_t id, Sprite topTex, Sprite sideTex, Sprite bottomTex, RendererType rendererType,
          bool noClip);
};
#endif //MYCRAFT_ANDROIDSTUDIO_BLOCK_H
