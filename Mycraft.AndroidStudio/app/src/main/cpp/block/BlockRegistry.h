//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H
#define MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H


#include "Block.h"

class BlockRegistry {
private:
    static Block **registry;

    static void registerBlock(uint8_t id, Sprite topTex, Sprite sideTex, Sprite bottomTex,
                              RendererType type = RendererType::Solid, bool noClip = false);

    static void registerBlock(uint8_t id, Sprite allTex, RendererType type = RendererType::Solid,
                              bool noClip = false);

public:
    static void initialize();

    static bool isTransparent(uint8_t id);

    static Block *getBlock(uint8_t id);
};


#endif //MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H
