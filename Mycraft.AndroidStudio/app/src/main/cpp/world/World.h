//
// Created by twome on 17/06/2018.
//

#ifndef MYCRAFT_ANDROIDSTUDIO_WORLD_H
#define MYCRAFT_ANDROIDSTUDIO_WORLD_H

#define RENDERPASS_SOLID 1
#define RENDERPASS_FLUID 2

#include "Chunk.h"

class World {
private:
    Chunk **chunkArray;
    int chunkArrayLen;

public:
    void render(int pass);

    void setBlock(int x, int y, int z, unsigned char block);

    unsigned char getBlock(int x, int y, int z);

    void addChunk(Chunk *chunk);

    World();
};


#endif //MYCRAFT_ANDROIDSTUDIO_WORLD_H
