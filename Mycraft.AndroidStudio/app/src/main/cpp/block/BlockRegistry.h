//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H
#define MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H


#include "Block.h"

class BlockRegistry {
private:
    static Block** registry;
    static void registerBlock(uint8_t id, TEXTURE topTex, TEXTURE sideTex, TEXTURE bottomTex);
    static void registerBlock(uint8_t id, TEXTURE allTex);
    static void registerBlock(uint8_t id, TEXTURE topTex, TEXTURE sideTex, TEXTURE bottomTex, RendererType type);
    static void registerBlock(uint8_t id, TEXTURE allTex, RendererType type);
public:
    static void initialize();
    static bool isFluid(uint8_t id);
    static bool isTransparent(uint8_t id);
    static bool isPlant(uint8_t id);
    static Block* getBlock(uint8_t id);
};


#endif //MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H
