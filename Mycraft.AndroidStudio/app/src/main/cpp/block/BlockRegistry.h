//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H
#define MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H


#include "Block.h"

class BlockRegistry {
private:
    static Block** registry;
    static void registerBlock(unsigned char id, TEXTURE topTex, TEXTURE sideTex, TEXTURE bottomTex);
    static void registerBlock(unsigned char id, TEXTURE allTex);
    static void registerBlock(unsigned char id, TEXTURE topTex, TEXTURE sideTex, TEXTURE bottomTex, RendererType type);
    static void registerBlock(unsigned char id, TEXTURE allTex, RendererType type);
public:
    static void initialize();
    static bool isFluid(unsigned char id);
    static bool isTransparent(unsigned char id);
    static bool isPlant(unsigned char id);
    static Block* getBlock(unsigned char id);
};


#endif //MYCRAFT_ANDROIDSTUDIO_BLOCKREGISTRY_H
