//
// Created by twome on 17/06/2018.
//

#include "Sprite.h"
#include "Block.h"

Block::Block(uint8_t id, Sprite topTex, Sprite sideTex, Sprite bottomTex,
             RendererType rendererType, bool noClip)
        : id(id), topTex(topTex), sideTex(sideTex), bottomTex(bottomTex),
          rendererType(rendererType), noClip(noClip) {
}
